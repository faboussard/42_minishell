/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdlib.h>
#include "parser.h"

int check_last_token_pipe(t_minishell *minishell)
{
	t_token_list *last_token = ft_lstlast_token(minishell->list_tokens);
	if (ft_lstsize_token(minishell->list_tokens) == 1 && last_token->e_operator == PIPE) {
		print_operator_syntax_error(last_token);
		return 1;
	}
	return 0;
}


int check_consecutive_redirect_tokens(t_token_list *current_token)
{
	t_token_list *next_token = current_token->next;
	if (is_redirect_token(current_token) && is_redirect_token(next_token)) {
		print_operator_syntax_error(current_token);
		return 1;
	}
	return 0;
}

int check_operator_followed_by_pipe(t_token_list *current_token)
{
	t_token_list *next_token = current_token->next;
	if (current_token->e_type == OPERATOR && next_token->e_operator == PIPE) {
		print_operator_syntax_error(next_token);
		return 1;
	}
	return 0;
}

int check_last_token_redirect(t_minishell *minishell)
{
	t_token_list *last_token = ft_lstlast_token(minishell->list_tokens);
	if (last_token != NULL && is_redirect_token(last_token))
	{
		print_operator_syntax_error(last_token);
		return 1;
	}
	return 0;
}

int check_syntax(t_minishell *minishell)
{
	t_token_list *iterator;

	if (minishell->list_tokens != NULL)
	{
		iterator = minishell->list_tokens;
		while (iterator != NULL && iterator->next != NULL)
		{
			if (iterator->e_operator == HERE_DOC && iterator->next->e_type != OPERATOR && iterator->next != NULL)
				return (0);
			if (check_consecutive_redirect_tokens(iterator))
				return (1);
			if (check_operator_followed_by_pipe(iterator))
				return (1);
			iterator = iterator->next;
		}
		if (check_last_token_redirect(minishell))
			return (1);
		if (check_last_token_pipe(minishell))
			return 1;
		return 0;
	}
	return 1;
}
