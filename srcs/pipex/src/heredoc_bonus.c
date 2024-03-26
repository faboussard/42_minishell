/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:23:43 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/26 08:42:21 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

bool	is_here_doc(t_pipex *p, char *str)
{
	if (!str)
		return (0);
	if (!str[0] || str[0] != 'h')
		return (0);
	if (!str[1] || str[1] != 'e')
		return (0);
	if (!str[2] || str[2] != 'r')
		return (0);
	if (!str[3] || str[3] != 'e')
		return (0);
	if (!str[4] || str[4] != '_')
		return (0);
	if (!str[5] || str[5] != 'd')
		return (0);
	if (!str[6] || str[6] != 'o')
		return (0);
	if (!str[7] || str[7] != 'c')
		return (0);
	if (str[8])
		return (0);
	p->here_doc = 1;
	return (1);
}

static void	writing_in_heredoc(t_pipex *p, char *limiter)
{
	size_t	limiter_len;
	size_t	input_len;
	char	*input;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		input = get_next_line(STDIN_FILENO);
		input_len = ft_strlen(input) - 1;
		if (input_len == limiter_len && !ft_strncmp(input, limiter,
				limiter_len))
		{
			free(input);
			close(p->fd_in);
			exit(0);
		}
		ft_putstr_fd(input, p->fd_in);
		free(input);
	}
}

static void	here_doc(t_pipex *p, char *limiter)
{
	check_and_delete_if_tmp_file_exists("/tmp/.tmp_heredoc");
	p->fd_in = open("/tmp/.tmp_heredoc", O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (p->fd_in < 0)
		exit_msg(NULL, "No /tmp/ directory found", -1);
	p->pid1 = safe_fork(p);
	if (p->pid1 == 0)
		writing_in_heredoc(p, limiter);
	else
	{
		while (waitpid(-1, &(p->status), 0) && errno != 10)
			;
		close(p->fd_in);
	}
}

void	handle_heredoc(t_pipex *p, char *limiter, int *i, int ac)
{
	if (ac < 6)
	{
		ft_putstr_fd("pipex: ", 2);
		exit_msg(NULL, "Invalid number of arguments", 2);
	}
	*i = 3;
	here_doc(p, limiter);
}
