/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:54:44 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/25 11:39:55 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

pid_t	safe_fork(t_pipex *p)
{
	pid_t	my_pid;

	my_pid = fork();
	if (my_pid == -1)
	{
		close_pipes(p);
		print_name_and_exit_perror(p, "fork", errno);
	}
	return (my_pid);
}

void	safe_dup2(t_pipex *p, int old_fd, int new_fd)
{
	int	my_dup;

	my_dup = dup2(old_fd, new_fd);
	if (my_dup == -1)
		print_name_and_exit_perror(p, "dup2", errno);
}

void	close_pipes(t_pipex *p)
{
	if (!p)
		return ;
	if (p->pipe_fd[0] && p->pipe_fd[0] > 0)
		close(p->pipe_fd[0]);
	if (p->pipe_fd[1] && p->pipe_fd[1] > 0)
		close(p->pipe_fd[1]);
}

void	check_null_cmd(int ac, char **av, int i)
{
	while (i < ac - 1)
	{
		if (!av[i] || !av[i][0])
		{
			ft_putstr_fd("pipex: ", 2);
			exit_msg_pipex(NULL, SYNTAX_ERROR, 2);
		}
		i++;
	}
}
