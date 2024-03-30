/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdbool.h>


bool define_operator_token(t_token *new_token, const char *string, const char *operator[9])
{
	int i = 0;

	while (i < 9)
	{
		if (operator[i] != NULL && !ft_strncmp(string, operator[i], ft_strlen(string)))
		{
			new_token->e_type = OPERATOR;
			new_token->e_operator = i;
			return true;
		}
		i++;
	}
	return false;
}


bool get_operator_token(t_token *new_token, const char *string)
{
	const char *operator[9] = {
			[OPEN_PARENTHESES] = "(",
			[CLOSE_PARENTHESES] = ")",
			[PIPE] = "|",
			[OUTPUT_REDIRECT] = ">",
			[INPUT_REDIRECT] = "<",
			[HERE_DOC] = "<<",
			[APPEND] = ">>"
	};

	return define_operator_token(new_token, string, operator);
}


bool	is_redirect_token(t_token *token)
{
	if (token == NULL || token->e_type != OPERATOR)
		return (0);
	return (token->e_operator == INPUT_REDIRECT
			|| token->e_operator == OUTPUT_REDIRECT
			|| token->e_operator == HERE_DOC
			|| token->e_operator == APPEND);
}







