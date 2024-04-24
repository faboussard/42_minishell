/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/18 10:34:38 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdlib.h>
#include "parser.h"


void join_tokens(t_minishell *minishell, t_token_list **list)
{
	char *joined_name;
	t_token_list *t2;
	t_token_list *t1;

	t1 = (*list);
	t2 = (*list)->next;
	joined_name = ft_strjoin(t1->name, t2->name);
	free(t1->name);
	t1->name = ft_strdup(joined_name);
	free(joined_name);
	if (t1->name == NULL)
		exit_msg(minishell, "Malloc failed at tokenization", 1);
	del_next_token(&t1);
	define_token_types(COMMAND, NO_BUILTIN, NO_OPERATOR, t1);
}

void join_between_quotes_handler(t_minishell *minishell, t_token_list **list, enum e_token_operators op)
{
	int count;

	count = 1;
	if (*list == NULL || (*list)->next == NULL || (*list)->next->next == NULL)
		return;
	(*list) = (*list)->next;
	while ((*list) && (*list)->next)
	{
		if ((*list)->next->e_operator == op)
		{
			define_token_types(COMMAND, NO_BUILTIN, NO_OPERATOR, (*list));
			(*list) = (*list)->next;
			(*list) = (*list)->next;
			count++;
		}
		if (count == 2)
			return;
		else if (count == 1)
			join_tokens(minishell, list);
	}
}

void join_between_quotes(t_minishell *minishell, t_token_list **list)
{
	t_token_list *cpy;
	int quote_type;

	cpy = *list;
	while (*list != NULL && (*list)->next != NULL)
	{
		quote_type = (*list)->e_operator;
		if ((quote_type == DOUBLE_QUOTE || quote_type == SINGLE_QUOTE) && quote_type == (int)(*list)->next->e_operator)
		{
			join_tokens(minishell, list);
			change_iterator_name_to_empty_string(minishell, list, "\0");
			continue ;
		}
		else if ((quote_type == DOUBLE_QUOTE || quote_type == SINGLE_QUOTE) && check_if_more_tokens(list, quote_type))
		{
			join_between_quotes_handler(minishell, list, quote_type);
			if ((*list) == NULL)
				break;
		}
		else
			(*list) = (*list)->next;
	}
	*list = cpy;
}

void join_between_spaces(t_minishell *minishell, t_token_list **list)
{
	t_token_list *cpy;

	if (list == NULL || *list == NULL)
		return ;
	cpy = *list;
	while (*list != NULL && (*list)->next != NULL)
	{
		while ((*list)->e_operator == IS_SPACE)
			*list = (*list)->next;
		if ((*list) != NULL && (*list)->next != NULL && (*list)->next->e_operator != IS_SPACE)
		{
			if (is_redirect_token_or_pipe((*list)->next))
				*list = (*list)->next;
			else if ((*list)->e_operator != IS_SPACE)
				join_tokens(minishell, list);
			if ( (*list)->next == NULL)
				break;
		}
		*list = (*list)->next;
	}
	*list = cpy;
}