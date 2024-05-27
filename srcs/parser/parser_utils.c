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
			join_tokens_safely(minishell, list, cpy);
			continue ;
		}
		*list = (*list)->next;
	}
	*list = cpy;
}

void	token_rework(t_minishell *m)
{
	if (m->list_tokens == NULL)
		return ;
	ft_list_remove_if_same_type(&m->list_tokens, (void *)TO_DELETE, cmp);
	join_between_quotes(m, &m->list_tokens);
	supress_two_consecutive_empty_names(m, &m->list_tokens);
	remove_empty_in_words(&m->list_tokens);
	ft_list_remove_if_same_op(&m->list_tokens, (void *)SINGLE_QUOTE, cmp);
	ft_list_remove_if_same_op(&m->list_tokens, (void *)DOUBLE_QUOTE, cmp);
	if (m->list_tokens == NULL)
		return ;
	join_between_spaces(m, &m->list_tokens);
	ft_list_remove_if_same_op(&m->list_tokens, (void *)IS_SPACE, cmp);
}

void	replace_empty_name(t_minishell *m, t_token_list *iterator)
{
	char			*new_list_name;

	new_list_name = ft_strdup("''");
	if (new_list_name == NULL)
		exit_msg(m, "Malloc failed at join between spaces", ENOMEM);
	free_safely_str(&(iterator->name));
	iterator->name = new_list_name;
}
