/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:20:51 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/28 11:26:44 by mbernard         ###   ########.fr       */
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

void	safe_dup2(t_minishell *minishell, int old_fd, int new_fd)
{
	int	my_dup;

	my_dup = dup2(old_fd, new_fd);
	if (my_dup == -1)
		print_name_and_exit_perror(minishell, "dup2", errno);
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
