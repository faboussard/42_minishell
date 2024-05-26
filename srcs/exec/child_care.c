/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_care.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:22:26 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/24 09:52:07 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signals.h"

static void	first_child(t_minishell *m, t_process_list *pl)
{
	if (handle_in_out(m, pl, &(pl->fd_in)) == 0 && pl->dev_null == 0)
	{
		signal_interrupt();
		m->pid1 = m_safe_fork(m);
		if (m->pid1 == 0)
		{
			m_safe_dup2(m, pl->fd_in, STDIN_FILENO);
			if (pl->fd_out != STDOUT_FILENO)
			{
				m_safe_dup2(m, pl->fd_out, STDOUT_FILENO);
				close(pl->fd_out);
			}
			else
				m_safe_dup2(m, m->pipe_fd[WRITE_END], STDOUT_FILENO);
			close_pipes(m->pipe_fd);
			my_execve(m, pl);
		}
		else
			close_and_redirect_pipe_to_stdin(m, pl);
	}
	else
		close_and_redirect_pipe_to_stdin(m, pl);
}

static void	last_child(t_minishell *m, t_process_list *pl, bool *files_failed)
{
	if (handle_in_out(m, pl, &(m->tmp_in)) == 0 && pl->dev_null == 0)
	{
		signal_interrupt();
		m->pid2 = m_safe_fork(m);
		if (m->pid2 == 0)
		{
			m_safe_dup2(m, m->tmp_in, STDIN_FILENO);
			close(m->tmp_in);
			if (pl->fd_out != STDOUT_FILENO)
			{
				m_safe_dup2(m, pl->fd_out, STDOUT_FILENO);
				close(pl->fd_out);
			}
			my_execve(m, pl);
		}
		else
			close_fds(m->tmp_in, pl->fd_out);
	}
	else
	{
		*files_failed = 1;
		close_pipes(m->pipe_fd);
		close_fds(m->tmp_in, pl->fd_out);
	}
}

static void	middle_child(t_minishell *m, t_process_list *pl)
{
	if (handle_in_out(m, pl, &(m->tmp_in)) == 0 && pl->dev_null == 0)
	{
		signal_interrupt();
		m->pid1 = m_safe_fork(m);
		if (m->pid1 == 0)
		{
			m_safe_dup2(m, m->tmp_in, STDIN_FILENO);
			close(m->tmp_in);
			if (pl->fd_out != STDOUT_FILENO)
			{
				m_safe_dup2(m, pl->fd_out, STDOUT_FILENO);
				close(pl->fd_out);
			}
			else
				m_safe_dup2(m, m->pipe_fd[WRITE_END], STDOUT_FILENO);
			close_pipes(m->pipe_fd);
			my_execve(m, pl);
		}
		else
			close_and_redirect_pipe_to_stdin(m, pl);
	}
	else
		close_and_redirect_pipe_to_stdin(m, pl);
}

static void	wait_children_and_give_exit_status(t_minishell *m,
		bool files_failed)
{
	waitpid(m->pid2, &(m->status), 0);
	while (waitpid(-1, NULL, 0) && errno != 10)
		;
	if (files_failed == 1)
		m->status = 1;
	else if (files_failed == 0)
		manage_signal_code(m);
}

void	exec_several_cmds(t_minishell *m, t_process_list *p_list)
{
	size_t			i;
	t_process_list	*pl;
	bool			files_failed;

	pl = p_list;
	files_failed = 0;
	if (safe_pipe(m) == 0)
		return ;
	first_child(m, pl);
	pl = pl->next;
	i = 1;
	while (++i < m->total_commands)
	{
		if (safe_pipe(m) == 0)
			return ;
		middle_child(m, pl);
		pl = pl->next;
	}
	last_child(m, pl, &files_failed);
	wait_children_and_give_exit_status(m, files_failed);
	close_fds(pl->fd_in, pl->fd_out);
}
