/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:20:54 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/03 11:29:32 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	check_and_delete_if_tmp_file_exists(char *tmp_file)
{
	if (access(tmp_file, F_OK) == 0)
	{
		if (unlink(tmp_file) == -1)
			perror("");
	}
}

static void	writing_in_heredoc(t_minishell *m, char *limiter)
{
	size_t	limiter_len;
	size_t	input_len;
	char	*input;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		input = get_next_line(STDIN_FILENO);
//			expand_input
		input_len = ft_strlen(input) - 1;
		if (input_len == limiter_len && !ft_strncmp(input, limiter,
				limiter_len))
		{
			free(input);
			close(m->fd_in);
			exit(0);
		}
		ft_putstr_fd(input, m->fd_in);
		free(input);
	}
}

void	here_doc(t_minishell *m, char *limiter)
{
	check_and_delete_if_tmp_file_exists("/tmp/.tmp_heredoc");
	m->fd_in = open("/tmp/.tmp_heredoc", O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (m->fd_in < 0)
		perror("No /tmp/ directory found");
	// A CHANGER, pas d'exit du minishell
	m->pid1 = m_safe_fork(m);
	if (m->pid1 == 0)
		writing_in_heredoc(m, limiter);
	else
	{
		while (waitpid(-1, &(m->status), 0) && errno != 10)
			;
		close(m->fd_in);
	}
}
