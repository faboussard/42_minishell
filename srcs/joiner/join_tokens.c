/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/02 09:50:06 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "utils.h"
#include "parser.h"

int join_tokens(t_token_list **list)
{
	char *joined_name;
	t_token_list *t2;
	t_token_list *t1;

	t1 = (*list);
	t2 = (*list)->next;
	if (t2 == NULL)
		return 0;
	joined_name = ft_strjoin(t1->name, t2->name);
	if (joined_name == NULL)
		return (MALLOC_FAILED);
	free_safely_str(&(t1->name));
	t1->name = ft_strdup(joined_name);
	free_safely_str(&joined_name);
	if (t1->name == NULL)
		return (MALLOC_FAILED);
	del_next_token(&t1);
	define_token_types(COMMAND, NO_BUILTIN, NO_OPERATOR, t1);
	return (0);
}

void join_between_quotes_handler(t_token_list **list, enum e_token_operators op, t_minishell *m)
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
		{
			if (join_tokens(list) == MALLOC_FAILED)
				exit_msg_minishell(m, "Malloc failed at join_tokens", ENOMEM);
		}
	}
}

void join_between_quotes(t_minishell *m, t_token_list **list)
{
	t_token_list *cpy;
	int quote_type;

	cpy = *list;
	while (*list != NULL && (*list)->next != NULL)
	{
		quote_type = (*list)->e_operator;
		if ((quote_type == DOUBLE_QUOTE || quote_type == SINGLE_QUOTE) && quote_type == (int)(*list)->next->e_operator)
		{
			if (join_tokens(list) == MALLOC_FAILED)
				exit_msg_minishell(m, "Malloc failed at join_tokens", ENOMEM);
			change_token_name(list, "\0");
			continue ;
		}
		else if ((quote_type == DOUBLE_QUOTE || quote_type == SINGLE_QUOTE) && check_if_more_tokens(list, quote_type))
		{
			join_between_quotes_handler(list, quote_type,m);
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

	cpy = *list;
	do_join_not_spaces(minishell, list);
	*list = cpy;
}

char *join_all(t_minishell *minishell, t_token_list **list)
{
	t_token_list *iterator;
	char *new_table;
	char *temp;
	size_t total_length;

	temp = NULL;
	new_table = NULL;
	total_length = 0;
	iterator = *list;
	while (iterator)
	{
		total_length += ft_strlen(iterator->name);
		iterator = iterator->next;
	}
	new_table = ft_calloc(total_length + 1, sizeof(char));
	if (new_table == NULL)
		exit_msg_minishell(minishell, "Memory allocation failed for command table array", ENOMEM);
	iterator = *list;
	while (iterator)
		join_token_name(minishell, temp, &iterator, &new_table);
	return (new_table);
}

