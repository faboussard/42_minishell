/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "utils.h"
#include "parser.h"

void add_token_to_list(t_token_list **list_tokens, t_token_list *new_token)
{
	t_token_list	*last;

	if (*list_tokens != NULL)
	{
		last = ft_lstlast_token(*list_tokens);
		if (last != NULL)
			last->next = new_token;
	}
	else
		*list_tokens = new_token;
	new_token->next = NULL;
}

void ft_list_remove_if_same_op(t_token_list **begin_list, void *data_ref, int (*cmp)())
{
	t_token_list *current;
	t_token_list *temp;

	if (begin_list == NULL || *begin_list == NULL)
		return ;
	current = *begin_list;
	while (current != NULL)
	{
		if ((*cmp)(current->e_operator, data_ref) == 0)
		{
			temp = current->next;
			remove_node_token(begin_list, current);
			current = temp;
		}
		else
			current = current->next;
	}
}

void ft_list_remove_if_same_type(t_token_list **begin_list, void *data_ref, int (*cmp)())
{
	t_token_list *current;
	t_token_list *temp;

	if (begin_list == NULL || *begin_list == NULL)
		return ;
	current = *begin_list;
	while (current != NULL)
	{
		if ((*cmp)(current->e_type, data_ref) == 0)
		{
			temp = current->next;
			remove_node_token(begin_list, current);
			current = temp;
		}
		else
			current = current->next;
	}
}


void remove_node_token(t_token_list **begin_list, t_token_list *node_to_remove)
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
	if (current == node_to_remove && current)
	{
		if (previous_node != NULL)
			previous_node->next = current->next;
		else
			*begin_list = current->next;
		free_token(current);
	}
}

int	ft_lstsize_token(t_token_list *lst)
{
	int	i;
	int	list_size;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	list_size = i;
	return (list_size);
}