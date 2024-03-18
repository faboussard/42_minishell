/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                               		        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/22 12:10:15 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "../libft/inc/libft.h"

void	print_error(char *error)
{
	if (error != NULL)
		ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
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


