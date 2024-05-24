/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:20:54 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/06 14:38:22 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "utils.h"
#include "signals.h"

char	*parse_input_for_heredoc(t_minishell *m, char *original_input)
{
	char			*input_after_expand;
	t_token_list	*heredoc_token_list;

	heredoc_token_list = NULL;
	transform_to_token(m, original_input, &heredoc_token_list);
	expander(m, &heredoc_token_list, 1);
	ft_list_remove_if_same_type(&heredoc_token_list, (void *)TO_DELETE, cmp);
	input_after_expand = join_all(m, &heredoc_token_list);
	ft_lstclear_token(&heredoc_token_list);
	return (input_after_expand);
}

void	handle_expand(t_minishell *m, t_process_list *pl, char *input)
{
	char	*input_after_expand;

	input_after_expand = parse_input_for_heredoc(m, input);
	if (input_after_expand != NULL)
	{
		ft_putstr_fd(input_after_expand, pl->fd_in);
		free_safely_str(&(input_after_expand));
	}
	else
		ft_putstr_fd(input, pl->fd_in);
}

static void close_and_clear_heredoc(t_minishell *m, t_process_list *pl, char **input)
{
	free_safely_str(&(*input));
	close_all_fds(m, pl);
	free_minishell(m);
	exit(0);
}


static void	writing_in_heredoc(t_minishell *m, t_process_list *pl,
		t_token_list *limiter, int *fd_to_use)
{
	size_t	limiter_len;
	size_t	input_len;
	char	*input;

	limiter_len = ft_strlen(limiter->name);
	while (1)
	{
		input = get_next_line(STDIN_FILENO);
		if (input == NULL)
			exit_msg_minishell(m, "minishell: warning: leaving heredoc", 0);
		input_len = ft_strlen(input) - 1;
		if (input_len == limiter_len && !ft_strncmp(input, limiter->name,
				limiter_len))
			close_and_clear_heredoc(m, pl, &input);
		if (limiter->is_quoted_delimiter == 1)
			ft_putstr_fd(input, *fd_to_use);
		else
			handle_expand(m, pl, input);
		free_safely_str(&(input));
	}
}

void	here_doc(t_minishell *m, t_token_list *limiter, int *fd_to_use, t_process_list *pl)
{
	int	here_doc_pid;

	check_and_delete_if_tmp_file_exists(HERE_DOC_TMP_FILE);
	close_fds(*fd_to_use, m->tmp_in);
	close_fds(pl->fd_in, pl->fd_out);

	*fd_to_use = open(HERE_DOC_TMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (*fd_to_use < 0)
	{
		perror("No /tmp/ directory found");
		return ;
	}
	ignore_sigquit();
	ignore_sigint();
	here_doc_pid = m_safe_fork(m);
	if (here_doc_pid == 0)
		writing_in_heredoc(m, m->pl, limiter, fd_to_use);
	else
	{
		if (waitpid(here_doc_pid, &(m->status), 0) == -1)
			exit_msg_minishell(m, "waitpid error", 1);
		close(*fd_to_use);
	}
}
