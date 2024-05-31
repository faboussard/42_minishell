/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:20:54 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/30 17:06:23 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "signals.h"

static char	*parse_input_for_heredoc(t_minishell *m, char *original_input)
{
	char			*input_after_expand;
	t_token_list	*heredoc_token_list;

	heredoc_token_list = NULL;
	transform_to_token(m, original_input, &heredoc_token_list);
	expander(m, &heredoc_token_list, 1);
	ft_list_remove_if_same_type(&heredoc_token_list, (void *)TO_DELETE, cmp);
	if (heredoc_token_list == NULL)
		return (NULL);
	input_after_expand = join_in_heredoc(&heredoc_token_list);
	ft_lstclear_token(&heredoc_token_list);
	if (input_after_expand == NULL)
	{
		free_safely_str(&original_input);
		exit_msg(m, "Malloc failed at heredoc. Child process exited.", ENOMEM);
	}
	return (input_after_expand);
}

static void	handle_expand(t_minishell *m, char *input,
							 const int *fd_to_use)
{
	char	*input_after_expand;

	input_after_expand = parse_input_for_heredoc(m, input);
	if (input_after_expand != NULL)
	{
		ft_putstr_fd(input_after_expand, *fd_to_use);
		free_safely_str(&(input_after_expand));
	}
	else
		ft_putstr_fd(input, *fd_to_use);
}

static void	close_and_clear_heredoc(t_minishell *m, t_process_list *pl,
		char **input)
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
	char	*input;
	int		fd;

	set_signals_heredoc();
	limiter_len = ft_strlen(limiter->name);
	while (1)
	{
		input = get_next_line(STDIN_FILENO);
		if (input == NULL)
			exit_msg(m, "minishell: warning: leaving heredoc", 0);
		if (ft_strlen(input) - 1 == limiter_len
			&& !ft_strncmp(input, limiter->name, limiter_len))
			close_and_clear_heredoc(m, pl, &input);
		fd = open(pl->here_doc_file, O_CREAT | O_WRONLY | O_APPEND, 0666);
		if (fd < 0)
			perror_exit_heredoc(m, pl, &input);
		if (limiter->is_quoted_delimiter == 1)
			ft_putstr_fd(input, *fd_to_use);
		else
			handle_expand(m, input, fd_to_use);
		close(fd);
		free_safely_str(&(input));
	}
}

void	here_doc(t_minishell *m, t_token_list *limiter, int *fd_to_use,
		t_process_list *pl)
{
	int	here_doc_pid;

	if (m->interrupted_here_doc == 1)
		return ;
	fill_heredoc_file_name(m, pl);
	close_fds(*fd_to_use, m->tmp_in);
	close_fds(pl->fd_in, pl->fd_out);
	*fd_to_use = open(pl->here_doc_file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (*fd_to_use < 0)
	{
		perror("No /tmp/ directory found");
		return ;
	}
	close(*fd_to_use);
	here_doc_pid = m_safe_fork(m);
	if (here_doc_pid == 0)
		writing_in_heredoc(m, pl, limiter, fd_to_use);
	else
	{
		if (waitpid(here_doc_pid, &(m->status), 0) == -1)
			exit_msg(m, "waitpid error", 1);
	}
	manage_signal_code(m, 1);
}
