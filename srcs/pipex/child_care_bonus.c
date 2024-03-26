/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_care_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:04:04 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/25 20:13:10 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	close_and_redirect_pipe_to_stdin(t_pipex *p)
{
	close(p->pipe_fd[WRITE_END]);
	close(p->fd_in);
	p->fd_in = p->pipe_fd[READ_END];
	safe_dup2(p, p->pipe_fd[READ_END], STDIN_FILENO);
}

static void	first_child(t_pipex *p, char *cmd, char **env)
{
	if (p->fd_in > 0 && p->dev_null == 0)
	{
		p->pid1 = safe_fork(p);
		if (p->pid1 == 0)
		{
			safe_dup2(p, p->fd_in, STDIN_FILENO);
			safe_dup2(p, p->pipe_fd[WRITE_END], STDOUT_FILENO);
			close(p->fd_in);
			close_pipes(p);
			exec(p, cmd, env);
		}
		else
			close_and_redirect_pipe_to_stdin(p);
	}
	else
		close_and_redirect_pipe_to_stdin(p);
}

static void	last_child(t_pipex *p, char *cmd, char **env)
{
	if (p->fd_out > 0)
	{
		p->pid2 = safe_fork(p);
		if (p->pid2 == 0)
		{
			close_pipes(p);
			safe_dup2(p, p->tmp_in, STDIN_FILENO);
			safe_dup2(p, p->fd_out, STDOUT_FILENO);
			close(p->fd_out);
			exec(p, cmd, env);
		}
		else
			close_and_redirect_pipe_to_stdin(p);
	}
	else
		close_pipes(p);
}

static void	middle_child(t_pipex *p, char *cmd, char **env)
{
	if (p->fd_in > 0)
	{
		p->pid1 = safe_fork(p);
		if (p->pid1 == 0)
		{
			safe_dup2(p, p->tmp_in, STDIN_FILENO);
			safe_dup2(p, p->pipe_fd[WRITE_END], STDOUT_FILENO);
			close_pipes(p);
			exec(p, cmd, env);
		}
		else
			close(p->pipe_fd[WRITE_END]);
	}
	safe_dup2(p, p->pipe_fd[READ_END], p->tmp_in);
	close(p->pipe_fd[READ_END]);
}

void	child_care(t_pipex *p, char *cmd, char **env, int child)
{
	if (pipe(p->pipe_fd) == -1)
		exit_msg_pipex(p, "Error creating the pipe", -1);
	if (child == 1)
		first_child(p, cmd, env);
	else if (child == 3)
		last_child(p, cmd, env);
	else
		middle_child(p, cmd, env);
}
