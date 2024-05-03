/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:20:51 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/03 11:54:06 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

pid_t	m_safe_fork(t_minishell *minishell)
{
	pid_t	my_pid;

	my_pid = fork();
	if (my_pid == -1)
	{
		close_pipes(minishell->pipe_fd);
		print_name_and_exit_perror(minishell, "fork", errno);
	}
	return (my_pid);
}

void	m_safe_dup2(t_minishell *minishell, int old_fd, int new_fd)
{
	int	my_dup;

	my_dup = dup2(old_fd, new_fd);
	if (my_dup == -1)
		print_name_and_exit_perror(minishell, "dup2", errno);
}

bool	safe_pipe(t_minishell *m)
{
	if (pipe(m->pipe_fd) == -1)
	{
		ft_putendl_fd("Error creating the pipe", 2);
		m->status = -1;
		return (0);
	}
	return (1);
}

void	close_pipes(int *pipe_fd)
{
	if (!pipe_fd)
		return ;
	if (pipe_fd[0] && pipe_fd[0] > 0)
		close(pipe_fd[0]);
	if (pipe_fd[1] && pipe_fd[1] > 0)
		close(pipe_fd[1]);
}

void	close_fds(int fd_in, int fd_out)
{
	if (fd_in >= 3)
		close(fd_in);
	if (fd_out >= 3)
		close(fd_out);
}
