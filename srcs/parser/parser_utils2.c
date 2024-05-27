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

void	skip_operator(t_token_list **list, enum e_token_operators op)
{
	while ((*list) && (*list)->e_operator == op)
		*list = (*list)->next;
}

void	do_join_not_spaces(t_minishell *minishell, t_token_list **list)
{
	t_token_list	*cpy;

	cpy = *list;
	while (*list != NULL && (*list)->next != NULL)
	{
		skip_operator(list, IS_SPACE);
		if ((*list) != NULL && (*list)->next != NULL
			&& (*list)->next->e_operator != IS_SPACE)
		{
			if (is_redirect_token_or_pipe((*list)->next)
				|| is_redirect_token_or_pipe(*list))
			{
				*list = (*list)->next;
				continue ;
			}
			else if ((*list)->e_operator != IS_SPACE
					&& (*list)->in_env_token == 0)
			{
				if (join_tokens(list) == MALLOC_FAILED)
					join_tokens_safely(minishell, list, cpy);
				continue ;
			}
		}
		if ((*list) == NULL)
			break ;
		*list = (*list)->next;
	}
}
