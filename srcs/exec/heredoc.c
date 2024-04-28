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
#include "parser.h"
#include "utils.h"

char *parse_input_for_heredoc(t_minishell *minishell, char *original_input)
{
	char *input_after_expand;
	t_token_list *heredoc_token_list;

	heredoc_token_list = NULL;
	transform_to_token(minishell, original_input, &heredoc_token_list);
	expander(minishell, &heredoc_token_list);
	ft_list_remove_if_same_type(&heredoc_token_list, (void *) TO_DELETE, cmp);
	input_after_expand = join_all(minishell, &heredoc_token_list);
	ft_lstclear_token(&heredoc_token_list);
	return (input_after_expand);
}

void	handle_expand(t_minishell *m, char *input)
{
	char	*input_after_expand;

	input_after_expand = parse_input_for_heredoc(m, input);
	if (input_after_expand != NULL)
	{
		ft_putstr_fd(input_after_expand, m->fd_in);
		free_safely_str(input_after_expand);
	}
	else
		ft_putstr_fd(input, m->fd_in);;
}


static void	writing_in_heredoc(t_minishell *m, t_token_list *limiter, int stdin_fd)
{
	size_t	limiter_len;
	size_t	input_len;
	char	*input;

	limiter_len = ft_strlen(limiter->name);
	while (1)
	{
		input = get_next_line(stdin_fd);
		input_len = ft_strlen(input) - 1;
		if (input_len == limiter_len && !ft_strncmp(input, limiter->name,
				limiter_len))
		{
			free_safely_str(input);
			close(m->fd_in);
			exit(0);
		}
		if (limiter->is_quoted_delimiter == 1)
			ft_putstr_fd(input, m->fd_in);
		else
			handle_expand(m, input);
		free_safely_str(input);
	}
}

void	here_doc(t_minishell *m, t_token_list *limiter, int stdin_fd, int *fd_to_use)
{
    int here_doc_pid;

    check_and_delete_if_tmp_file_exists(HERE_DOC_TMP_FILE);
    close_fds(*fd_to_use, -1);
    *fd_to_use = open(HERE_DOC_TMP_FILE, O_CREAT | O_WRONLY | O_TRUNC , 0666);
	if (*fd_to_use < 0)
	{
		perror("No /tmp/ directory found");
		return ;
	}
    here_doc_pid = m_safe_fork(m);
	if (here_doc_pid == 0)
		writing_in_heredoc(m, limiter, stdin_fd);
	else
	{
		waitpid(here_doc_pid, &(m->status), 0); // && errno != 10);
		close(*fd_to_use);
	}
}
/*
 * Impossible de remplacer m->fd_in par un fd_here_doc local, fait foirer
 * la suite : un << compte wc -l donnera toujours 0 au lieu de compter
 * si on n'utilise pas fd_in
 */