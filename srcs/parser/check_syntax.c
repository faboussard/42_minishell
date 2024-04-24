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

/*RULES:
 *
 *
 *
 *
 *
 *
 * */

int check_consecutive_redirect_tokens(t_token_list *current_token)
{
	t_token_list *next_token;

	if (current_token->next == NULL)
		return (0);
	next_token = current_token->next;
	if (is_redirect_token(current_token) && is_redirect_token(next_token))
	{
		print_operator_syntax_error(current_token);
		return (1);
	}
	return (0);
}

int check_redirect_operator_followed_by_pipe(t_token_list *current_token)
{
	t_token_list *next_token;

	if (current_token->next == NULL)
		return (0);
	next_token = current_token->next;
	if (is_redirect_token(current_token) && next_token->e_operator == PIPE)
	{
		print_operator_syntax_error(next_token);
		return (1);
	}
	return (0);
}

int check_last_token_redirect_or_pipe(t_minishell *minishell)
{
	t_token_list *last_token;

	last_token = ft_lstlast_token(minishell->list_tokens);
	if (last_token != NULL && is_redirect_token_or_pipe(last_token))
	{
		print_operator_syntax_error(last_token);
		return (1);
	}
	return (0);
}

// REVOIR pour la question du here doc on execute ou on lqnce le message avant ??

static bool quote_should_not_be_seen_as_a_real_quote(char *str, char quote)
{
	bool first_quote_is_open;
	char other_quote;
	size_t j;

	if (quote == '\'')
		other_quote = '\"';
	else
		other_quote = '\'';
	first_quote_is_open = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] == other_quote)
			first_quote_is_open = !first_quote_is_open;
		j++;
	}
	return (first_quote_is_open);
}

int check_syntax(t_minishell *minishell)
{
	t_token_list *iterator;
	iterator = minishell->list_tokens;

	if (quote_should_not_be_seen_as_a_real_quote(minishell->user_input, '\''))
		return (1);
	if (quote_should_not_be_seen_as_a_real_quote(minishell->user_input, '\"'))
		return (1);
	if (check_last_token_redirect_or_pipe(minishell))
		return (1);

	while (iterator != NULL)
	{
		if (check_consecutive_redirect_tokens(iterator))
			return (1);
		if (check_redirect_operator_followed_by_pipe(iterator))
			return (1);
		iterator = iterator->next;
	}
	return (0);
}

int get_first_odd_quote(size_t quote_count, int first_odd_quote, int quote_type)
{
	if (quote_count % 2 != 0 && first_odd_quote == -1)
		first_odd_quote = quote_type;
	if (quote_count % 2 == 0 && first_odd_quote == quote_type)
		first_odd_quote = -1;
	return (first_odd_quote);
}

/* Idee de fonction pour gerer les quote qui ne generent pas une syntax error comme elles le devraient*/


size_t check_quotes(t_minishell *minishell)
{
	size_t quote_double;
	size_t quote_simple;
	int first_odd_quote;
	t_token_list *iterator;

	first_odd_quote = -1;
	quote_double = 0;
	quote_simple = 0;
	iterator = minishell->list_tokens;
	while (iterator != NULL)
	{
		if (iterator->e_operator == DOUBLE_QUOTE)
		{
			quote_double++;
			first_odd_quote = get_first_odd_quote(quote_double, first_odd_quote,
												  DOUBLE_QUOTE);
		}
		if (iterator->e_operator == SINGLE_QUOTE)
		{
			quote_simple++;
			first_odd_quote = get_first_odd_quote(quote_simple, first_odd_quote,
												  SINGLE_QUOTE);
		}
		iterator = iterator->next;
	}
	if (first_odd_quote != -1)
		return (print_quote_syntax_error(first_odd_quote), 1);
	else
		return (0);
}