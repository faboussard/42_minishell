/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:18:22 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/03 17:14:54 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	open_fd_infile(t_minishell *m, t_process_list *pl, int *fd_to_use)
{
	pl->dev_null = 0;
	if (pl->in_files_token->e_type == DELIMITER)
		*fd_to_use = open(HERE_DOC_TMP_FILE, O_RDONLY);
	else if (pl->in_files_token->e_type == IN_FILE)
		*fd_to_use = open(pl->in_files_token->name, O_RDONLY);
	else
		*fd_to_use = STDIN_FILENO;
	if (*fd_to_use < 0)
	{
		if (pl->in_files_token->e_type == DELIMITER)
			perror("minishell: /tmp/.tmp_heredoc");
		else
			print_name(m, pl->in_files_token->name);
		m->status = 1;
		pl->dev_null = 1;
		*fd_to_use = open("/dev/null", O_RDONLY);
		if (*fd_to_use < 0)
		{
			ft_putendl_fd("No /dev/null/ found", 2);
			return (1);
		}
	}
	return (0);
}

int	open_fd_outfile(t_minishell *m, t_process_list *pl, char *out)
{
	if (pl->out_files_token->e_type == OUT_FILE)
		pl->fd_out = open(out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (pl->out_files_token->e_type == APPEND_FILE)
		pl->fd_out = open(out, O_CREAT | O_WRONLY | O_APPEND, 0644);
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
	if (pl->fd_out != STDOUT_FILENO)
		close(pl->fd_out);
}
