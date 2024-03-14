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

//structure de bbuilint + options
//cd with only a relative or absolute path -> faire un strjoin
//&& transform_to_token->content + 1 == "-n" ->faire un strjoin

#include "lexer.h"
#include "general.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "../libft/inc/libft.h"
#include "error.h"


void cpy_string_operator(char operator[9][10])
{
	ft_strcpy(operator[OPEN_PARENTHESES], "(");
	ft_strcpy(operator[CLOSE_PARENTHESES], ")");
	ft_strcpy(operator[PIPE], "|");
	ft_strcpy(operator[INPUT_REDIRECT], ">");
	ft_strcpy(operator[OUTPUT_REDIRECT], "<");
	ft_strcpy(operator[HERE_DOC], "<<");
	ft_strcpy(operator[APPEND], ">>");
	ft_strcpy(operator[DOUBLE_QUOTE], "\"");
	ft_strcpy(operator[SINGLE_QUOTE], "'");
}

bool	define_operator(t_token *new_token, char *string)
{
	int		i;
	char	operator[9][10];

	i = 0;
	cpy_string_operator(operator);
	while (i < 9)
	{
		if (!ft_strncmp(string, operator[i], ft_strlen(string)))
		{
			define_token(OPERATOR, NO_BUILTIN, i, new_token);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

bool	is_redirect_token(t_token *token)
{
	if (token == NULL || token->e_type != OPERATOR)
		return (0);
	return (token->e_operator == INPUT_REDIRECT
			|| token->e_operator == OUTPUT_REDIRECT
			|| token->e_operator == HERE_DOC);
}

void	print_operator_syntax_error(t_token *token)
{
	enum e_token_operators	error;

	if (token == NULL)
		return (print_error("syntax error near unexpected token `newline'"));
	error = token->e_operator;
	if (error == OPEN_PARENTHESES)
		print_error("syntax error near unexpected token `('");
	else if (error == CLOSE_PARENTHESES)
		print_error("syntax error near unexpected token `)'");
	else if (error == PIPE)
		print_error("syntax error near unexpected token `|'");
	else if (error == INPUT_REDIRECT)
		print_error("syntax error near unexpected token `<'");
	else if (error == OUTPUT_REDIRECT)
		print_error("syntax error near unexpected token `>'");
	else if (error == HERE_DOC)
		print_error("syntax error near unexpected token `<<'");
	else if (error == APPEND)
		print_error("syntax error near unexpected token `>>'");
}







