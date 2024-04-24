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

/*RULES: ORDER IN CODE IS IMPORTANT
 * 1/ is pipe is the only token in the list : special message
 * 2 / two redirect cannot be consecutive
 * 3 / redirect operator or pile must be followed by a word
 * 4/ check quotes
 * */

int check_last_token_redirect_or_pipe(t_minishell *minishell)
{
	t_token_list *last_token;

	last_token = ft_lstlast_token(minishell->list_tokens);
	if (last_token->e_operator == PIPE)
	{
		print_error("minishell: syntax error: unexpected end of file");
		return (1);
	}
	if (is_redirect_token(last_token))
	{
		print_error("minishell: syntax error near unexpected token `newline'");
		return (1);
	}
	return (0);
}

int check_syntax(t_minishell *minishell)
{
	t_token_list *current_token;
	current_token = minishell->list_tokens;
	t_token_list *next_token;

	if (ft_lstsize_token(minishell->list_tokens) == 1 && current_token->e_operator == PIPE)
	{
		print_error("minishell: syntax error near unexpected token `|'");
		return (1);
	}
	while (current_token != NULL)
	{
		next_token = current_token->next;
		if (is_redirect_token_or_pipe(current_token) && is_redirect_token_or_pipe(next_token))
		{
			print_operator_syntax_error(current_token);
			return (1);
		}
		current_token = current_token->next;
	}
	if (check_last_token_redirect_or_pipe(minishell))
		return (1);
	return (0);
}
