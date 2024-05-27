/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/19 11:06:17 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "utils.h"
#include <stdlib.h>

void	define_append(t_minishell *m, t_token_list **list, t_token_list *cpy)
{
	if ((*list)->e_operator == OUTPUT_REDIRECT
		&& (*list)->next->e_operator == OUTPUT_REDIRECT)
	{
		join_tokens_safely(m, list, cpy);
		(*list)->e_type = OPERATOR;
		(*list)->e_operator = APPEND;
	}
}

void	define_here_doc(t_minishell *m, t_token_list **list, t_token_list *cpy)
{
	if ((*list)->e_operator == INPUT_REDIRECT
		&& (*list)->next->e_operator == INPUT_REDIRECT)
	{
		join_tokens_safely(m, list, cpy);
		(*list)->e_type = OPERATOR;
		(*list)->e_operator = HERE_DOC;
	}
}

void	define_heredoc_and_append(t_minishell *minishell, t_token_list **list)
{
	t_token_list	*cpy;

	if (list == NULL || *list == NULL)
		return ;
	cpy = *list;
	while (*list != NULL && (*list)->next != NULL)
	{
		define_here_doc(minishell, list, cpy);
		define_append(minishell, list, cpy);
		if ((*list) == NULL)
			break ;
		*list = (*list)->next;
	}
	*list = cpy;
}
