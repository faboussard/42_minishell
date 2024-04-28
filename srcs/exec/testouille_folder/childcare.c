/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childcare.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:04:04 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/30 17:38:25 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	close_and_redirect_pipe_to_stdin(t_minishell *m)
{
	close(m->pipe_fd[WRITE_END]);
	close(m->fd_in);
	m->fd_in = m->pipe_fd[READ_END];
	safe_dup2(m, m->pipe_fd[READ_END], STDIN_FILENO);
}

static void	first_child(t_minishell *m, char *cmd, char **env)
{
	if (m->fd_in > 0 && m->dev_null == 0)
	{
		m->pid1 = safe_fork(m);
		if (m->pid1 == 0)
		{
			safe_dup2(m, m->fd_in, STDIN_FILENO);
			safe_dup2(m, m->pipe_fd[WRITE_END], STDOUT_FILENO);
			close(m->fd_in);
			close_pipes(m);
			my_execve(m, cmd, env);
		}
		else
			close_and_redirect_pipe_to_stdin(m);
	}
	else
		close_and_redirect_pipe_to_stdin(m);
}

static void	last_child(t_minishell *m, char *cmd, char **env)
{
	if (m->fd_out > 0)
	{
		m->pid2 = safe_fork(m);
		if (m->pid2 == 0)
		{
			close_pipes(m);
			safe_dup2(m, m->tmp_in, STDIN_FILENO);
			safe_dup2(m, m->fd_out, STDOUT_FILENO);
			close(m->fd_out);
			my_execve(m, cmd, env);
		}
		else
			close_and_redirect_pipe_to_stdin(m);
	}
	else
		close_pipes(m);
}

static void	middle_child(t_minishell *m, char *cmd, char **env)
{
	if (m->fd_in > 0)
	{
		m->pid1 = safe_fork(m);
		if (m->pid1 == 0)
		{
			safe_dup2(m, m->tmp_in, STDIN_FILENO);
			safe_dup2(m, m->pipe_fd[WRITE_END], STDOUT_FILENO);
			close_pipes(m);
			my_execve(m, cmd, env);
		}
		else
			close(m->pipe_fd[WRITE_END]);
	}
	safe_dup2(m, m->pipe_fd[READ_END], m->tmp_in);
	close(m->pipe_fd[READ_END]);
}

/*
void	child_care(t_minishell *m, char *cmd, char **env, int child)
{
	if (mipe(m->pipe_fd) == -1)
		exit_msg_pipex(m, "Error creating the pipe", -1);
	if (child == 1)
		first_child(m, cmd, env);
	else if (child == 3)
		last_child(m, cmd, env);
	else
		middle_child(m, cmd, env);
}
*/
