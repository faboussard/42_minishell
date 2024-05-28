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
#include "signals.h"

char	*parse_input_for_heredoc(t_minishell *m, char *original_input)
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

static void	close_and_clear_heredoc(t_minishell *m, t_process_list *pl,
		char **input, int fd_to_use)
{
	free_safely_str(&(*input));
	free_safely_str(&(pl->here_doc_file));
	close(fd_to_use);
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

	set_signals_heredoc();
	limiter_len = ft_strlen(limiter->name);
	while (1)
	{
		input = get_next_line(STDIN_FILENO);
		if (input == NULL)
			exit_msg(m, "minishell: warning: leaving heredoc", 0);
		input_len = ft_strlen(input) - 1;
		if (input_len == limiter_len && !ft_strncmp(input, limiter->name,
				limiter_len))
			close_and_clear_heredoc(m, pl, &input, *fd_to_use);
		if (limiter->is_quoted_delimiter == 1)
			ft_putstr_fd(input, *fd_to_use);
		else
			handle_expand(m, pl, input);
		free_safely_str(&(input));
	}
}

static void	fill_heredoc_file_name(t_minishell *m, t_process_list *pl)
{
	int		num;
	char	*str_num;

	if (pl->here_doc_file != NULL)
		check_and_delete_if_tmp_file_exists(pl);
	num = INT_MIN;
	while (pl->here_doc_file == NULL || access(pl->here_doc_file, F_OK) == 0)
	{
		free_safely_str(&(pl->here_doc_file));
		str_num = ft_itoa(num);
		if (str_num == NULL)
			exit_msg(m, "Malloc failed at heredoc", ENOMEM);
		pl->here_doc_file = ft_strjoin("/tmp/.tmp_heredoc", str_num);
		free_safely_str(&str_num);
		if (pl->here_doc_file == NULL)
			exit_msg(m, "Malloc failed at heredoc", ENOMEM);
		num++;
	}
}

void	here_doc(t_minishell *m, t_token_list *limiter, int *fd_to_use,
		t_process_list *pl)
{
	int	here_doc_pid;

	fill_heredoc_file_name(m, pl);
	close_fds(*fd_to_use, m->tmp_in);
	close_fds(pl->fd_in, pl->fd_out);
	*fd_to_use = open(pl->here_doc_file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (*fd_to_use < 0)
	{
		perror("No /tmp/ directory found");
		return ;
	}
	here_doc_pid = m_safe_fork(m);
	if (here_doc_pid == 0)
		writing_in_heredoc(m, pl, limiter, fd_to_use);
	else
	{
		if (waitpid(here_doc_pid, &(m->status), 0) == -1)
			exit_msg(m, "waitpid error", 1);
		close(*fd_to_use);
	}
	manage_signal_code(m);
}
