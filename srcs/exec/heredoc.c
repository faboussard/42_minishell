/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:20:54 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/11 10:13:44 by mbernard         ###   ########.fr       */
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

static void	handle_expand(t_minishell *m, char *input, char *input_after_expand)
{
	char **split;

	split = NULL;
	if (ft_strchr(input, '$') != NULL)
	{
			split = ft_split(input, ' ');
			int i = 0;
			while (split[i])
			{
				expand_dollar_string(&split[i], m);
				input_after_expand = ft_calloc(1, 1);
				input_after_expand = ft_strjoin(input_after_expand, split[i]);
				i++;
			}
	}
	if (input_after_expand  != NULL)
		ft_putstr_fd(input_after_expand, m->fd_in);
	else
		ft_putstr_fd(input, m->fd_in);
	if (input_after_expand  != NULL)
		free(input_after_expand);
	if (split != NULL)
		ft_free_tab(split);
}
static void	writing_in_heredoc(t_minishell *m, char *limiter)
{
	size_t	limiter_len;
	size_t	input_len;
	char	*input;
	char	*input_after_expand;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		input_after_expand = NULL;
		input = get_next_line(STDIN_FILENO);
		input_len = ft_strlen(input) - 1;
		if (input_len == limiter_len && !ft_strncmp(input, limiter,
				limiter_len))
		{
			free(input);
			close(m->fd_in);
			exit(0);
		}
		handle_expand(m, input, input_after_expand);
		free(input);
	}
}

void	here_doc(t_minishell *m, char *limiter)
{
	check_and_delete_if_tmp_file_exists(HERE_DOC_TMP_FILE);
	m->fd_in = open(HERE_DOC_TMP_FILE, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (m->fd_in < 0)
	{
		perror("No /tmp/ directory found");
		return ;
	}
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
