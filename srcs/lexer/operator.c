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

#include <stdbool.h>
#include "lexer.h"

bool define_operator_token(t_token_list *new_token, const char *string, const char *operator[13])
{
	int i = 0;
	size_t len;

	len = ft_strlen(string) + 1;
	while (i < 13)
	{
		if (operator[i] != NULL
		&& (!ft_strncmp(string, operator[i], len)
		|| (i == IS_SPACE && ft_isspace(string[0]))))
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

bool	is_redirect_token_or_pipe(t_token_list *token)
{
	if (token == NULL || token->e_type != OPERATOR)
		return (0);
	return (token->e_operator == INPUT_REDIRECT
			|| token->e_operator == OUTPUT_REDIRECT
			|| token->e_operator == HERE_DOC
			|| token->e_operator == APPEND
			|| token->e_operator == PIPE);
}

bool char_is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '$' || c == '\"' || c == '\'' || c == ' ');
}







