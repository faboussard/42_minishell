/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_care.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:22:26 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/09 15:13:15 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	close_and_redirect_pipe_to_stdin(t_minishell *m)
{
	if (m->pipe_fd[WRITE_END] >= 0)
		close(m->pipe_fd[WRITE_END]);
	if (m->fd_in >= 0)
		close(m->fd_in);
	m->fd_in = m->pipe_fd[READ_END];
	m_safe_dup2(m, m->pipe_fd[READ_END], STDIN_FILENO);
}

static void	first_child(t_minishell *m)
{
	if (m->fd_in >= 0 && m->process_list->dev_null == 0)
	{
		m->pid1 = m_safe_fork(m);
		if (m->pid1 == 0)
		{
			m_safe_dup2(m, m->fd_in, STDIN_FILENO);
			m_safe_dup2(m, m->pipe_fd[WRITE_END], STDOUT_FILENO);
			close(m->fd_in);
			close_pipes(m->pipe_fd);
			my_execve(m, m->process_list);
		}
		else
			close_and_redirect_pipe_to_stdin(m);
	}
	else
		close_and_redirect_pipe_to_stdin(m);
}

static void	last_child(t_minishell *m, t_process_list *process_list)
{
	if (m->fd_out > 0)
	{
		m->pid2 = m_safe_fork(m);
		if (m->pid2 == 0)
		{
			close_pipes(m->pipe_fd);
			m_safe_dup2(m, m->tmp_in, STDIN_FILENO);
			if (m->fd_out != STDOUT_FILENO)
			{
				m_safe_dup2(m, m->fd_out, STDOUT_FILENO);
				close(m->fd_out);
			}
			my_execve(m, process_list);
		}
		else
		{
			close_pipes(m->pipe_fd);
			close(m->tmp_in);
			close_fds(m->fd_in, m->fd_out);
		}
	}
	else
		close_pipes(m->pipe_fd);
}

static void	middle_child(t_minishell *m, t_process_list *process_list)
{
	if (m->fd_in >= 0)
	{
		m->pid1 = m_safe_fork(m);
		if (m->pid1 == 0)
		{
			m_safe_dup2(m, m->tmp_in, STDIN_FILENO);
			m_safe_dup2(m, m->pipe_fd[WRITE_END], STDOUT_FILENO);
			close_pipes(m->pipe_fd);
			my_execve(m, process_list);
		}
		else
			close(m->pipe_fd[WRITE_END]);
	}
	m_safe_dup2(m, m->pipe_fd[READ_END], m->tmp_in);
	close(m->pipe_fd[READ_END]);
}

static void	wait_children_and_give_exit_status(t_minishell *m)
{
	int	status;

	status = 0;
	waitpid(m->pid2, &status, 0);
	while (waitpid(-1, NULL, 0) && errno != 10)
		;
	m->status = WEXITSTATUS(status);
}

void	exec_several_cmds(t_minishell *m, t_process_list *process_list)
{
	size_t			i;
	t_process_list	*pl;

	pl = process_list;
	if (safe_pipe(m) == 0)
		return ;
	open_fd_infile(m, pl->in_files_token);
	first_child(m);
	pl = pl->next;
	i = 1;
	while (++i < m->total_commands)
	{
		if (safe_pipe(m) == 0)
			return ;
		middle_child(m, pl);
		pl = pl->next;
	}
	open_fd_outfile(m, pl->out_files_token->name);
	if (safe_pipe(m) == 0)
		return ;
	last_child(m, pl);
	wait_children_and_give_exit_status(m);
	close_fds(m->fd_in, m->fd_out);
}
