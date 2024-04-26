/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/19 11:06:17 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "utils.h"
#include <stdlib.h>

static int cmp(int op1, int op2)
{
	return (op1 - op2);
}

void remove_empty_in_words(t_token_list **list)
{
	t_token_list *cpy;

	if (list == NULL || *list == NULL)
		return;
	cpy = *list;
	while (*list != NULL && (*list)->next != NULL)
	{
		if (ft_strcmp((*list)->name, "\0") == 0 && (*list)->next->e_type == COMMAND)
			(*list)->e_operator = DOUBLE_QUOTE;
		if (ft_strcmp((*list)->next->name, "\0") == 0 && (*list)->e_type == COMMAND)
			(*list)->next->e_operator = DOUBLE_QUOTE;
		*list = (*list)->next;
	}
	*list = cpy;
}


void supress_two_consecutive_empty_names(t_minishell *minishell, t_token_list **list)
{
	t_token_list *cpy;

	if (list == NULL || *list == NULL)
		return;
	cpy = *list;
	while (*list != NULL && (*list)->next != NULL)
	{
		if (ft_strcmp((*list)->name, "\0") == 0 && strcmp((*list)->next->name, "\0") == 0)
		{
			join_tokens(minishell, list);
			continue;
		}
		*list = (*list)->next;
	}
	*list = cpy;
}


void token_rework(t_minishell *minishell)
{
	if (minishell->list_tokens == NULL)
		return ;
	ft_list_remove_if_same_type(&minishell->list_tokens, (void *) TO_DELETE, cmp);
	join_between_quotes(minishell, &minishell->list_tokens);
	supress_two_consecutive_empty_names(minishell, &minishell->list_tokens);
	remove_empty_in_words(&minishell->list_tokens);
	ft_list_remove_if_same_op(&minishell->list_tokens, (void *) SINGLE_QUOTE, cmp);
	ft_list_remove_if_same_op(&minishell->list_tokens, (void *) DOUBLE_QUOTE, cmp);
	ft_list_remove_if_same_op(&minishell->list_tokens, (void *) DOLLAR, cmp);
	join_between_spaces(minishell, &minishell->list_tokens);
	ft_list_remove_if_same_op(&minishell->list_tokens, (void *) IS_SPACE, cmp);
}

int parse_input(t_minishell *minishell)
{
	char *string;
	string = minishell->user_input;

	transform_to_token(minishell, string);
	define_heredoc_and_append(minishell, &minishell->list_tokens);
	if (check_quotes(minishell))
		return (1);
	expander(minishell);
	token_rework(minishell);
	if (check_syntax(minishell) == 1)
	{
		minishell->status = set_or_get_last_status(2, 0);
		return (1);
	}
	if (minishell->list_tokens == NULL)
		return (1);
	token_requalification(minishell->list_tokens);
	create_envp_table(minishell);
	create_process_list(minishell);
	return (0);
}
