/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/21 15:00:00 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "utils.h"
#include <stdlib.h>


bool print_quote_syntax_error(enum e_token_operators operator)
{
	if (operator == SINGLE_QUOTE)
		return (print_error(
				"minishell: unexpected EOF while looking for matching `''\nminishell: syntax error: unexpected end of file"),
				1);
	else if (operator == DOUBLE_QUOTE)
		return (print_error(
				"minishell: unexpected EOF while looking for matching `\"'\nminishell: syntax error: unexpected end of file"),
				1);
	return (0);
}

bool print_operator_syntax_error(t_token_list *token)
{
	int	error;

	error = token->e_operator;
	if (error == PIPE && token->next != NULL)
		print_error("syntax error: unexpected end of file");
	else if (error == PIPE && token->next == NULL)
		print_error("minishell: syntax error near unexpected token `|'");
	else if (error == INPUT_REDIRECT)
		return (print_error("minishell: syntax error near unexpected token `<'"), 1);
	else if (error == OUTPUT_REDIRECT)
		return (print_error("minishell: syntax error near unexpected token `>'"), 1);
	else if (error == HERE_DOC)
		return (print_error("minishell: syntax error near unexpected token `<<'"), 1);
	else if (error == APPEND)
		return (print_error("minishell: syntax error near unexpected token `>>'"), 1);
	return (1);
}