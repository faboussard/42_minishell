/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:18:22 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/16 21:57:14 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	manage_fd_error(t_minishell *m, t_process_list *pl, int *fd_to_use)
{
	if (pl->in_files_list->e_type == DELIMITER)
		perror("minishell: heredoc file can't be opened");
	else
		print_name(m, pl->in_files_list->name);
	m->status = 1;
	pl->dev_null = 1;
	*fd_to_use = open("/dev/null", O_RDONLY);
	if (*fd_to_use < 0)
		ft_putendl_fd("Couldn't open /dev/null/", 2);
}

int	open_fd_infile(t_minishell *m, t_process_list *pl, char *name, int *fd_to_use)
{
	enum e_token_type	infile_type;

	pl->dev_null = 0;
	if (pl->in_files_list != NULL)
	{
		infile_type = pl->in_files_list->e_type;
		close_fds(*fd_to_use, 0);
		if (infile_type == DELIMITER)
			*fd_to_use = open(HERE_DOC_TMP_FILE, O_RDONLY);
		else if (infile_type == IN_FILE)
			*fd_to_use = open(pl->out_files_list->name, O_RDONLY);
	}
	else
		pl->fd_in = STDIN_FILENO;
	if (*fd_to_use < 0)
	{
		manage_fd_error(m, pl, fd_to_use);
		return (1);
	}
	return (0);
}

int	open_fd_outfile(t_minishell *m, t_process_list *pl, char *out)
{
	if (pl->out_files_list != NULL)
	{
		if (pl->out_files_list->e_type == OUT_FILE)
			pl->fd_out = open(out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (pl->out_files_list->e_type == APPEND_FILE)
			pl->fd_out = open(out, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else
		pl->fd_out = STDOUT_FILENO;
	if (pl->fd_out < 0)
	{
		print_name_and_give_status(m, out, 1);
		return (1);
	}
	return (0);
}

void	handle_in_out(t_minishell *m, t_process_list *pl, int *fd_in)
{
	if (pl->out_files_list != NULL)
	{
		if (pl->in_files_list->e_type == DELIMITER)
			here_doc(m, pl->in_files_list, fd_in, pl);
		// À REVOIR POUR BIEN DONNER LE BON NOM
		if (open_fd_infile(m, pl, fd_in))
			return;
	}
	//open_fd_outfile(m, pl, pl->out_files_list->name);
}

void	close_and_redirect_pipe_to_stdin(t_minishell *m, t_process_list *pl)
{
	if (m->pipe_fd[WRITE_END] > 0)
		close(m->pipe_fd[WRITE_END]);
	if (pl->fd_in >= 3)
		close(pl->fd_in);
	if (m->tmp_in >= 3)
		close(m->tmp_in);
	m->tmp_in = m->pipe_fd[READ_END];
	if (pl->fd_out != STDOUT_FILENO)
		close(pl->fd_out);
}