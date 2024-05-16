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
		if (ft_strncmp(string, iterator->target, ft_strlen(string)) == 0)
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


char *expand_sigil(char *string, t_minishell *minishell)
{
	char *final_string;

	if (ft_isdigit(*string))
		final_string = ft_strdup(string + 1);
	else
		final_string = identify_envp_string(string, minishell);
	return (final_string);
}

void update_quote_counts(t_token_list *token, int *single_quote_count, int *double_quote_count)
{
	if (token->e_operator == SINGLE_QUOTE)
		(*single_quote_count)++;
	else if (token->e_operator == DOUBLE_QUOTE)
		(*double_quote_count)++;
}

void define_to_delete_tokens(t_token_list *const *list)
{
	(*list)->e_type = TO_DELETE;
	(*list)->next->e_type = TO_DELETE;
}

void process_dollar_token(t_minishell *minishell, t_token_list **list, int single_quote_count, int double_quote_count)
{
	char *expanded_string;

	if (ft_strncmp((*list)->next->name, "?", 2) == 0)
		change_name_to_status(minishell, *list);
	else
	{
		if (single_quote_count % 2 != 0 && double_quote_count % 2 == 0)
			return ;
		if (!ft_isalnum((*list)->next->name[0]) && (*list)->next->name[0] != '_')
			(*list)->e_operator = 0;
		else
		{
			expanded_string = expand_sigil((*list)->next->name, minishell);
			if (expanded_string != (*list)->next->name)
			{
				join_tokens(minishell, list);
				change_token_name(minishell, list, expanded_string);
				free_safely_str(&expanded_string);
				return;
			}
			else
				define_to_delete_tokens(list);
		}
	}
}

void expand_tokens(t_minishell *minishell, t_token_list *iterator, int *single_quote_count, int *double_quote_count)
{
	while (iterator != NULL && iterator->next != NULL)
	{
		if (iterator->e_operator == HERE_DOC)
			handle_delimitor(&iterator);
		else if (iterator->e_operator == DOUBLE_QUOTE || iterator->e_operator == SINGLE_QUOTE)
			update_quote_counts(iterator, single_quote_count, double_quote_count);
		else if (iterator->e_operator == DOLLAR)
		{
			if (is_redirect_token(iterator->next) && iterator->next->next != NULL &&
				iterator->next->next->e_operator == IS_SPACE)
			{
				iterator->e_operator = 0; // to keep le dollar
				iterator = iterator->next;
				continue;
			}
			if (iterator->next->e_operator == DOUBLE_QUOTE || iterator->next->e_operator == SINGLE_QUOTE)
				update_quote_counts(iterator->next, single_quote_count, double_quote_count);
			process_dollar_token(minishell, &iterator, *single_quote_count, *double_quote_count);
		}
		if (iterator == NULL)
			break ;
		iterator = iterator->next;
	}
}

void expander(t_minishell *minishell, t_token_list **list)
{
	t_token_list *iterator;
	int single_quote_count;
	int double_quote_count;

	single_quote_count = 0;
	double_quote_count = 0;
	iterator = *list;
	expand_tokens(minishell, iterator, &single_quote_count, &double_quote_count);
}




