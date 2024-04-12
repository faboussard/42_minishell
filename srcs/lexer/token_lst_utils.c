/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdlib.h>

static void	move_cursor(t_token_list **cursor, t_token_list **previous_node)
{
	*previous_node = *cursor;
	*cursor = (*cursor)->next;
}

void	ft_list_remove_if(t_token_list **begin_list, char *to_compare,
						  void (*free_fct)(void *))
{
	t_token_list *t2;
	t_token_list *t1;

	t1 = *begin_list;
	t2 = (*begin_list)->next;
	while (t1 != NULL)
	{
		if (ft_strcmp(to_compare, t1->name) == 0)
		{
			t1->next = t2->next;
			free_token(t2);
			t1 = t1->next;
		}
		else
			t1 = t1->next;
	}
}