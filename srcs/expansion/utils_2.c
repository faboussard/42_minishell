/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/11 17:01:49 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include "parser.h"

char *identify_envp_string(char *string, t_minishell *minishell)
{
	t_envp_list *iterator;
	char *target_without_equal_sign;
	size_t len;

	iterator = minishell->list_envp;
	len = ft_strlen(string) + 1;
	while (iterator != NULL)
	{
		if (ft_strchr(iterator->target, '='))
			target_without_equal_sign = trim_equal_sign(iterator->target);
		else
			target_without_equal_sign = ft_strdup(iterator->target);
		if (target_without_equal_sign == NULL)
			exit_msg_minishell(minishell, "Malloc failed at identify_envp_string", ENOMEM);
		if (ft_strncmp(string, target_without_equal_sign, len) == 0)
			string = getString(string, minishell, iterator);
		free_safely_str(&target_without_equal_sign);
		iterator = iterator->next;
	}
	return (string);
}

void update_quote_counts(t_token_list *token, int *single_quote_count, int *double_quote_count)
{
	if (token->e_operator == SINGLE_QUOTE)
		(*single_quote_count)++;
	else if (token->e_operator == DOUBLE_QUOTE)
		(*double_quote_count)++;
}

void change_to_expansion(t_minishell *m, t_token_list **list, char **expanded_string)
{
	join_tokens(m, list);
	change_token_name(list, (*expanded_string));
}

void add_quotes_count(t_token_list *iterator, int *single_quote_count, int *double_quote_count)
{
	if (iterator->next->e_operator == DOUBLE_QUOTE || iterator->next->e_operator == SINGLE_QUOTE)
		update_quote_counts(iterator->next, single_quote_count, double_quote_count);
}

int s_quote_after_d_quote_and_dollar(t_token_list **list, int single_quote_count, int double_quote_count)
{
	t_token_list *iterator;

	iterator = *list;
	if (iterator == NULL || iterator->next == NULL)
		return (0);
	iterator = iterator->next;
	while (iterator)
	{
		while (iterator->e_operator == IS_SPACE)
			iterator = iterator->next;
		if (iterator->e_operator == SINGLE_QUOTE && single_quote_count % 2 == 0 && double_quote_count % 2 != 0)
			return (1);
		else
			return (0);
	}
	return (0);
}
