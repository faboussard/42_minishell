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
#include "utils.h"
#include <stdlib.h>

int	cmp(int op1, int op2)
{
	return (op1 - op2);
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
			if (join_tokens(list) == MALLOC_FAILED)
				join_tokens_safely(minishell, list, cpy);
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
	if (minishell->list_tokens == NULL)
		return ;
	join_between_spaces(minishell, &minishell->list_tokens);
	ft_list_remove_if_same_op(&minishell->list_tokens, (void *)IS_SPACE, cmp);
}
