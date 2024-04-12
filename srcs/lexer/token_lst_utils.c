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

void	ft_list_remove_if(t_token_list **begin_list, char *content_ref)
{
	t_token_list	*to_free;

	if (*begin_list)
	{
		if (ft_strcmp((*begin_list)->name, content_ref) == 0)
		{
			to_free = *begin_list;
			*begin_list = (*begin_list)->next;
			free_token(to_free);
			ft_list_remove_if(begin_list, content_ref);
		}
		else
			ft_list_remove_if(&(*begin_list)->next, content_ref);
	}
}
