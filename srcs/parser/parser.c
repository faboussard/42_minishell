/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/09 22:13:07 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include <stdlib.h>

int	cmp(int op1, int op2)
{
	return (op1 - op2);
}

int tokenize_input(t_minishell *m, char *string)
{
	transform_to_token(m, string, &m->list_tokens);
	if (m->list_tokens == NULL)
		return (0);
	define_heredoc_and_append(m, &m->list_tokens);
	return (1);
}

int rework_tokens(t_minishell *m)
{
	token_rework(m);
	return (m->list_tokens != NULL);
}


int requalify_tokens(t_minishell *m)
{
	if (m->list_tokens == NULL)
		return (0);
	token_requalification(m->list_tokens);
	return (1);
}

void create_environment_table(t_minishell *m)
{
	create_envp_table(m);
}

void	remove_empty_in_words(t_token_list **list)
{
	t_token_list	*cpy;

	if (list == NULL || *list == NULL)
		return ;
	cpy = *list;
	while (*list != NULL && (*list)->next != NULL)
	{
		if (ft_strcmp((*list)->name, "\0") == 0
			&& (*list)->next->e_type == COMMAND)
			(*list)->e_operator = DOUBLE_QUOTE;
		if (ft_strcmp((*list)->next->name, "\0") == 0
			&& (*list)->e_type == COMMAND)
			(*list)->next->e_operator = DOUBLE_QUOTE;
		*list = (*list)->next;
	}
	*list = cpy;
}

void	supress_two_consecutive_empty_names(t_minishell *minishell,
		t_token_list **list)
{
	t_token_list	*cpy;

	if (list == NULL || *list == NULL)
		return ;
	cpy = *list;
	while (*list != NULL && (*list)->next != NULL)
	{
		if (ft_strcmp((*list)->name, "\0") == 0 && strcmp((*list)->next->name,
				"\0") == 0)
		{
			join_tokens(minishell, list);
			continue ;
		}
		*list = (*list)->next;
	}
	*list = cpy;
}

void	token_rework(t_minishell *minishell)
{
	if (minishell->list_tokens == NULL)
		return ;
	ft_list_remove_if_same_type(&minishell->list_tokens, (void *)TO_DELETE,
		cmp);
	join_between_quotes(minishell, &minishell->list_tokens);
	supress_two_consecutive_empty_names(minishell, &minishell->list_tokens);
	remove_empty_in_words(&minishell->list_tokens);
	ft_list_remove_if_same_op(&minishell->list_tokens, (void *)SINGLE_QUOTE,
		cmp);
	ft_list_remove_if_same_op(&minishell->list_tokens, (void *)DOUBLE_QUOTE,
		cmp);
	ft_list_remove_if_same_op(&minishell->list_tokens, (void *)DOLLAR, cmp);
	join_between_spaces(minishell, &minishell->list_tokens);
	ft_list_remove_if_same_op(&minishell->list_tokens, (void *)IS_SPACE, cmp);
}

int parse_input(t_minishell *m)
{
	char *string;

	if (m->list_envp == NULL)
		return (1);
	string = m->user_input;
	if (!tokenize_input(m, string))
		return (0);
	if (check_quotes(m))
		return (1);
	expander(m, &m->list_tokens);
	if (!rework_tokens(m))
		return (0);
	if (check_syntax(m) == 1)
	{
		m->status = set_or_get_last_status(2, 0);
		return (1);
	}
	if (!requalify_tokens(m))
		return (1);
	create_environment_table(m);
	create_process_list(m, &m->pl);
	m->total_commands += count_tokens_by_operator(m, PIPE);
	return (0);
}

