/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:18:22 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/24 20:00:44 by mbernard         ###   ########.fr       */
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
	if (pl->next == NULL)
		return ;
	*fd_to_use = open("/dev/null", O_RDONLY);
	if (*fd_to_use < 0)
		ft_putstr_fd("Couldn't open /dev/null/\n", 2);
}

int	open_fd_infile(t_minishell *m, t_process_list *pl, char *name,
		int *fd_to_use)
{
	enum e_token_type	infile_type;

	pl->dev_null = 0;
	if (pl->in_files_list != NULL)
	{
		if (pl->in_files_list->failed_expand == true)
		{
			print_name_and_msg(m, name, ": ambiguous redirect");
			return (1);
		}
		infile_type = pl->in_files_list->e_type;
		close_fds(*fd_to_use, 0);
		if (infile_type == DELIMITER)
			*fd_to_use = open(pl->here_doc_file, O_RDONLY);
		else if (infile_type == IN_FILE)
			*fd_to_use = open(name, O_RDONLY);
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
	t_process_list	tmp;

	if (pl->out_files_list != NULL)
	{
		tmp = *pl;
		while (tmp.out_files_list->next)
			tmp.out_files_list = tmp.out_files_list->next;
		if (tmp.out_files_list->e_type == OUT_FILE)
			pl->fd_out = open(out, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		else if (tmp.out_files_list->e_type == APPEND_FILE)
			pl->fd_out = open(out, O_CREAT | O_WRONLY | O_APPEND, 0664);
	}
	else if (pl->next != NULL && ft_strncmp(out, "/dev/null", 10) == 0)
		pl->fd_out = open("/dev/null", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	else
		pl->fd_out = STDOUT_FILENO;
	if (pl->fd_out < 0)
	{
		print_name_and_give_status(m, out, 1);
		return (1);
	}
	return (0);
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
	if (pl->fd_out != STDOUT_FILENO && pl->fd_out >= 3)
		close(pl->fd_out);
}
