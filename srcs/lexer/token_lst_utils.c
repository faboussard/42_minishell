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

void del_next_token(t_token_list **token)
{
	t_token_list *t2;
	t_token_list *t1;

	t1 = (*token);
	t2 = (*token)->next;
	t1->next = t2->next;
	free_token(t2);
}

void remove_node(t_token_list **begin_list, t_token_list *node_to_remove)
{
	t_token_list *current;
	t_token_list *previous_node;

	current = *begin_list;
	previous_node = NULL;
	while (current != NULL && current != node_to_remove)
	{
		previous_node = current;
		current = current->next;
	}
	if (current == node_to_remove)
	{
		if (previous_node != NULL)
			previous_node->next = current->next;
		else
			*begin_list = current->next;
		free_token(current);
	}
}

void ft_list_remove_if(t_token_list **begin_list, void *data_ref, int (*cmp)())
{
	t_token_list *current = *begin_list;
	t_token_list *temp;

	while (current != NULL)
	{
		if ((*cmp)(current->e_operator, data_ref) == 0)
		{
			temp = current->next;
			remove_node(begin_list, current);
			current = temp;
		}
		else
			current = current->next;
	}
}


void ft_list_remove_if2(t_token_list **begin_list, void *data_ref, int (*cmp)())
{
	t_token_list *current = *begin_list;
	t_token_list *temp;

	while (current != NULL)
	{
		if ((*cmp)(current->e_operator, data_ref) == 0)
		{
			temp = current->next;
			remove_node(begin_list, current);
			current = temp;
		}
		else
			current = current->next;
	}
}

