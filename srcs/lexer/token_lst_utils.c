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



void	ft_list_remove_if(t_token_list **begin_list, void *data_ref, int (*cmp)())
{
	t_token_list	*remove;
	t_token_list	*current;

	current = *begin_list;
	while (current && current->next)
	{
		if ((*cmp)(current->next->e_operator, data_ref) == 0)
		{
			remove = current->next;
			current->next = current->next->next;
			free_token(remove);
		}
		current = current->next;
	}
	current = *begin_list;
	if (current && (*cmp)(current->e_operator, data_ref) == 0)
	{
		*begin_list = current->next;
		free(current);
	}
}
