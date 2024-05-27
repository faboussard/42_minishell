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

bool	check_last_token_redirect_or_pipe(t_minishell *minishell)
{
	t_token_list	*last_token;

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

bool	check_consecutive_redirect(t_minishell *minishell)
{
	t_token_list	*next_token;
	t_token_list	*current_token;

	current_token = minishell->list_tokens;
	while (current_token != NULL && current_token->next != NULL)
	{
		next_token = current_token->next;
		if (is_redirect_token(current_token) && is_redirect_token(next_token))
			return (print_operator_syntax_error(next_token), 1);
		if (is_redirect_token(current_token)
			&& is_redirect_token_or_pipe(next_token))
			return (print_operator_syntax_error(next_token), 1);
		if (current_token->e_operator == PIPE && next_token->e_operator == PIPE)
			return (print_operator_syntax_error(next_token), 1);
		current_token = current_token->next;
	}
	return (0);
}

bool	check_syntax(t_minishell *minishell)
{
	if (minishell->list_tokens == NULL)
		return (0);
	if (minishell->list_tokens->e_operator == PIPE)
	{
		print_error("minishell: syntax error near unexpected token `|'");
		return (1);
	}
	if (check_consecutive_redirect(minishell))
		return (1);
	if (check_last_token_redirect_or_pipe(minishell))
		return (1);
	return (0);
}
