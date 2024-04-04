/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_care.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:22:26 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/04 08:51:49 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	close_and_redirect_pipe_to_stdin(t_minishell *m)
{
	close(m->pipe_fd[WRITE_END]);
	close(m->fd_in);
	m->fd_in = m->pipe_fd[READ_END];
	m_safe_dup2(m, m->pipe_fd[READ_END], STDIN_FILENO);
}

static void	first_child(t_minishell *m, char **cmd, char **env)
{
	if (m->fd_in > 0 && m->process_list->dev_null == 0)
	{
		m->pid1 = m_safe_fork(m);
		if (m->pid1 == 0)
		{
			m_safe_dup2(m, m->fd_in, STDIN_FILENO);
			m_safe_dup2(m, m->pipe_fd[WRITE_END], STDOUT_FILENO);
			close(m->fd_in);
			close_pipes(m->pipe_fd);
			my_execve(m->process_list->good_path, cmd, env, m);
		}
		else
			close_and_redirect_pipe_to_stdin(m);
	}
	else
		close_and_redirect_pipe_to_stdin(m);
}

static void	last_child(t_minishell *m, char **cmd, char **env)
{
	if (m->fd_out > 0)
	{
		m->pid2 = m_safe_fork(m);
		if (m->pid2 == 0)
		{
			close_pipes(m->pipe_fd);
			m_safe_dup2(m, m->tmp_in, STDIN_FILENO);
			m_safe_dup2(m, m->fd_out, STDOUT_FILENO);
			close(m->fd_out);
			my_execve(m->process_list->good_path, cmd, env, m);
		}
		else
			close_and_redirect_pipe_to_stdin(m);
	}
	else
		close_pipes(m->pipe_fd);
}

static void	middle_child(t_minishell *m, char **cmd, char **env)
{
	if (m->fd_in > 0)
	{
		m->pid1 = m_safe_fork(m);
		if (m->pid1 == 0)
		{
			m_safe_dup2(m, m->tmp_in, STDIN_FILENO);
			m_safe_dup2(m, m->pipe_fd[WRITE_END], STDOUT_FILENO);
			close_pipes(m->pipe_fd);
			my_execve(m->process_list->good_path, cmd, env, m);
		}
		else
			close(m->pipe_fd[WRITE_END]);
	}
	m_safe_dup2(m, m->pipe_fd[READ_END], m->tmp_in);
	close(m->pipe_fd[READ_END]);
}

void	exec_several_cmds(t_minishell *m, t_process_list *process_list)
{
	size_t			i;
	t_process_list	*pl;

	pl = process_list;
	if (safe_pipe(m) == 0)
		return ;
	first_child(m, pl->cmd_table, m->envp_table);
	pl = pl->next;
	i = 0;
	while (++i < m->total_commands)
	{
		if (safe_pipe(m) == 0)
			return ;
		middle_child(m, pl->cmd_table, m->envp_table);
		pl = pl->next;
	}
	open_fd_outfile(m, pl->out_files_list->name);
	if (safe_pipe(m) == 0)
		return ;
	last_child(m, pl->cmd_table, m->envp_table);
}
