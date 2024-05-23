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
	t_envp_list *iterator = minishell->list_envp;

	while (iterator != NULL)
	{
		if (ft_strncmp(string, iterator->target, ft_strlen(iterator->target) - 1) == 0)
		{
			if (check_special_char_after_expand(string, iterator->target))
				string = expand_sign(string, iterator->value);
			else
			{
				string = ft_strdup(iterator->value);
				if (string == NULL)
					exit_msg(minishell, "Malloc failed at identify_envp_string", ENOMEM);
			}
			return (string);
		}
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
	change_token_name(m, list, (*expanded_string));
	free_safely_str(expanded_string);
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
