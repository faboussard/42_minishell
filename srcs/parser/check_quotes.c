/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/21 15:00:00 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include <stdlib.h>

void	check_open_quote(bool *open_quote, int *opened_quote_type,
		t_token_list **iterator)
{
	(*opened_quote_type) = (int)(*iterator)->e_operator;
	(*open_quote) = true;
	while ((*open_quote) && (*iterator) != NULL)
	{
		(*iterator) = (*iterator)->next;
		if ((*iterator) && (int)(*iterator)->e_operator == (*opened_quote_type))
		{
			(*open_quote) = false;
			(*iterator) = (*iterator)->next;
		}
	}
}

bool	check_quotes(t_minishell *minishell)
{
	bool open_quote;
	int opened_quote_type;
	t_token_list *iterator;

	iterator = minishell->list_tokens;
	opened_quote_type = -1;
	open_quote = false;
	while (iterator != NULL)
	{
		if (iterator->e_operator == DOUBLE_QUOTE
			|| iterator->e_operator == SINGLE_QUOTE)
			check_open_quote(&open_quote, &opened_quote_type, &iterator);
		else
			iterator = iterator->next;
	}
	if (open_quote == true)
	{
		print_quote_syntax_error(opened_quote_type);
		return (1);
	}
	return (0);
}