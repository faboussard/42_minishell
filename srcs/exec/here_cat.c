/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:20:54 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/23 08:55:57 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	writing_in_here_cat(t_minishell *m)
{
	size_t	input_len;
	char	*input;

	while (1)
	{
		input = get_next_line(STDIN_FILENO);
		input_len = ft_strlen(input) - 1;
		if (input_len == limiter_len && !ft_strncmp(input, limiter,
				limiter_len))
		{
			free(input);
			close(m->fd_in);
			exit(0);
		}
		free(input);
	}
}

void	here_cat(t_minishell *m)
{
    int fd_in_cat;
	check_and_delete_if_tmp_file_exists(HERE_CAT_TMP_FILE);
	fd_in_cat = open(HERE_CAT_TMP_FILE, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (m->fd_in < 0)
	{
		perror("No /tmp/ directory found");
		return ;
	}
	// A CHANGER, pas d'exit du minishell
	m->pid1 = m_safe_fork(m);
	if (m->pid1 == 0)
		writing_in_here_cat(m);
	else
	{
		while (waitpid(-1, &(m->status), 0) && errno != 10)
			;
		close(m->fd_in);
	}
}
