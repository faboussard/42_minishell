/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

void expand_dollar_token(t_token_list *token, t_minishell *minishell)
{
	size_t	i;

	i = 0;
	if (token->name[1] == '(' && token->name[ft_strlen(token->name)] == ')')
	{
		while (token->name[i])
		{
			token->name[i] = token->name[i + 2];
			i++;
		}
	}
	else
	{
		while (token->name[i])
		{
			token->name[i] = token->name[i + 1];
			i++;
		}
	}
	token->name[i] = '\0';
}

void expand_tokens(t_minishell *minishell)
{
	t_token_list *iterator;

	iterator = minishell->list_tokens;
	while (iterator != NULL)
	{
		if (iterator->e_type == ARGUMENT)
		{
			if (iterator->name[0] == '$')
				expand_dollar_token(iterator, minishell);
//			else if (ft_strcmp(iterator->name, "$?") == 0)
//				expand_question_mark_token(iterator, minishell);
		}
		iterator = iterator->next;
	}
}
