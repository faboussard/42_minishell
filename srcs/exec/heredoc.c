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

void expand_dollar_string(char **string, t_minishell *minishell);

static void	writing_in_heredoc(t_minishell *m, char *limiter)
{
	size_t	limiter_len;
	size_t	input_len;
	char	*input;
	char	*input_after_expand;
	char **split;

	limiter_len = ft_strlen(limiter);
	input_after_expand = NULL;
	while (1)
	{
		input = get_next_line(STDIN_FILENO);
		split = ft_split(input, ' ');
		int i = 0;
		while (split[i])
		{
			expand_dollar_string(&split[i], m);
			input_after_expand = ft_calloc(1, 1);
			input_after_expand = ft_strjoin(input_after_expand, split[i]);
			i++;
		}
		ft_free_tab(split);
		input_len = ft_strlen(input) - 1;
		if (input_len == limiter_len && !ft_strncmp(input, limiter,
				limiter_len))
		{
			free(input);
			if (input_after_expand  != NULL)
				free(input_after_expand);
			close(m->fd_in);
			exit(0);
		}
		ft_putstr_fd(input_after_expand, m->fd_in);
		free(input);
		if (input_after_expand  != NULL)
			free(input_after_expand);
		input_after_expand = NULL;
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
