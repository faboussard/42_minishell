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

void	print_error(const char *error)
{
	if (error != NULL)
		ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	print_operator_syntax_error(t_token_list *token)
{
	int	error;

	error = token->e_operator;
	if (error == OPEN_PARENTHESES)
		return (print_error("syntax error near unexpected token `('"), 1);
	else if (error == CLOSE_PARENTHESES)
		return (print_error("syntax error near unexpected token `)'"), 1);
	else if (error == PIPE)
		return (print_error("syntax error near unexpected token `|'"), 1);
	else if (error == INPUT_REDIRECT)
		return (print_error("syntax error near unexpected token `<'"), 1);
	else if (error == OUTPUT_REDIRECT)
		return (print_error("syntax error near unexpected token `>'"), 1);
	else if (error == HERE_DOC)
		return (print_error("syntax error near unexpected token `<<'"), 1);
	else if (error == APPEND)
		return (print_error("syntax error near unexpected token `>>'"), 1);
	return (0);
}

void	exit_msg(t_minishell *minishell, char *msg, int error_code)
{
	if (minishell != NULL)
		free_minishell(minishell);
	ft_putendl_fd(msg, 2);
	exit(error_code);
}


