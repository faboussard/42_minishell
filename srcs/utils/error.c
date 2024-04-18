/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/11 13:43:13 by mbernard         ###   ########.fr       */
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
	if (token->next == NULL && error != PIPE)
		return (print_error("minishell: syntax error near unexpected token `newline'"), 1);
	if (error == OPEN_PARENTHESES)
		return (print_error("minishell: syntax error near unexpected token `('"), 1);
	else if (error == CLOSE_PARENTHESES)
		return (print_error("minishell: syntax error near unexpected token `)'"), 1);
	else if (error == PIPE)
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

void	exit_msg(t_minishell *minishell, char *msg, int error_code)
{
	ft_putendl_fd(msg, 2);
	if (minishell != NULL)
		free_minishell(minishell);
	exit(error_code);
}

void	print_cmd_perror(char *cmd, char *name, int err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(err), 2);
}
