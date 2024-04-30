/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:18:22 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/29 13:01:28 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	open_fd_infile(t_minishell *m, t_process_list *pl)
{
	pl->dev_null = 0;
	if (pl->in_files_token->e_type == DELIMITER)
		pl->fd_in = open(HERE_DOC_TMP_FILE, O_RDONLY);
	else if (pl->in_files_token->e_type == IN_FILE)
		pl->fd_in = open(pl->in_files_token->name, O_RDONLY);
	else
		pl->fd_in = STDIN_FILENO;
	if (pl->fd_in < 0)
	{
		if (pl->in_files_token->e_type == DELIMITER)
			perror("minishell: /tmp/.tmp_heredoc");
		else
			print_name(m, pl->in_files_token->name);
		m->status = 1;
		pl->dev_null = 1;
		pl->fd_in = open("/dev/null", O_RDONLY);
		if (pl->fd_in < 0)
		{
			ft_putendl_fd("No /dev/null/ found", 2);
			return (1);
		}
	}
	return (0);
}
/*
		mbernard@z1r9p2:/usr$ cd cdvwev
		bash: cd: cdvwev: No such file or directory
		mbernard@z1r9p2:/usr$ echo $?
		1
*/

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

int	dup_original_fds(t_minishell *m, int *in, int *out, size_t nb_cmds)
{
	if (m->pl->in_files_token->e_type != NO_TYPE || nb_cmds > 1)
		*in = dup(STDIN_FILENO);
	if (m->pl->out_files_token->e_type != NO_TYPE || nb_cmds > 1)
		*out = dup(STDOUT_FILENO);
	if (*in == -1 || *out == -1)
	{
		if (*in >= 0)
			close(*in);
		ft_putendl_fd("minishell : dup error", 2);
		m->status = 1;
		return (1);
	}
	return (0);
}

void	close_original_fds(t_minishell *m, int *in, int *out, size_t nb_cmds)
{
	if (m->pl->in_files_token->e_type != NO_TYPE || nb_cmds > 1)
	{
		if (dup2(*in, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2");
			m->status = 1;
		}
		close(*in);
	}
	if (m->pl->out_files_token->e_type != NO_TYPE || nb_cmds > 1)
	{
		if (dup2(*out, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2");
			m->status = 1;
		}
		close(*out);
	}
}

void	close_and_redirect_pipe_to_stdin(t_minishell *m, t_process_list *pl)
{
	if (m->pipe_fd[WRITE_END] >= 0)
		close(m->pipe_fd[WRITE_END]);
	if (pl->fd_in >= 0)
		close(pl->fd_in);
	pl->fd_in = m->pipe_fd[READ_END];
	if (pl->fd_out != STDOUT_FILENO)
		close(pl->fd_out);
	else
		m_safe_dup2(m, m->pipe_fd[READ_END], STDIN_FILENO);
}
