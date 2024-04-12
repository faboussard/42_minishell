/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/30 19:05:30 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdbool.h>


bool define_operator_token(t_token_list *new_token, const char *string, const char *operator[13])
{
	int i = 0;

	while (i < 13)
	{
		if (operator[i] != NULL && !ft_strcmp(string, operator[i]))
		{
			new_token->e_type = OPERATOR;
			new_token->e_operator = i;
			return (true);
		}
		i++;
	}
	return (false);
}


bool get_operator_token(t_token_list *new_token, const char *string)
{
	const char *operator[13] = {
			[OPEN_PARENTHESES] = "(",
			[CLOSE_PARENTHESES] = ")",
			[PIPE] = "|",
			[OUTPUT_REDIRECT] = ">",
			[INPUT_REDIRECT] = "<",
			[HERE_DOC] = "<<",
			[APPEND] = ">>",
			[DOUBLE_QUOTE] = "\"",
			[SINGLE_QUOTE] = "\'",
			[IS_SPACE] = " ",
			[DOLLAR] = "$"
	};
	return (define_operator_token(new_token, string, operator));
}


bool	is_redirect_token(t_token_list *token)
{
	if (token == NULL || token->e_type != OPERATOR)
		return (0);
	return (token->e_operator == INPUT_REDIRECT
			|| token->e_operator == OUTPUT_REDIRECT
			|| token->e_operator == HERE_DOC
			|| token->e_operator == APPEND);
}







