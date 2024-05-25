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

void ft_lsti_insert_after(t_token_list **current, t_token_list *new_token)
{
	if (current == NULL || *current == NULL || new_token == NULL)
		return;
	new_token->next = (*current)->next;
	(*current)->next = new_token;
}

int insert_env_token(char *string, t_token_list **current)
{
	t_token_list *new_token;

	new_token = ft_calloc(1, sizeof(t_token_list));
	if (new_token == NULL)
		return (MALLOC_FAILED);
	if (define_token(new_token, string) == MALLOC_FAILED)
	{
		free(new_token);
		return (MALLOC_FAILED);
	}
	new_token->in_env_token = 1;
	ft_lsti_insert_after(current, new_token);
	return (0);
}


void add_tokens_and_change_to_expansion(t_minishell *m, t_token_list **list, char *expanded_string)
{
	char **split;
	int i;
	t_token_list *current;

	i = 0;
	split = ft_split(expanded_string, ' ');
	if (split == NULL)
	{
		free(expanded_string);
		exit_msg_minishell(m, "Malloc failed at add_tokens_and_change_to_expansion", ENOMEM);
	}
	current = *list;
	while (split[i])
	{
		if (insert_env_token(split[i], &current) == MALLOC_FAILED)
		{
			ft_free_tab(&split);
			free(expanded_string);
			exit_msg_minishell(m, "Malloc failed at add_tokens_and_change_to_expansion", ENOMEM);
		}
		current = current->next;
		i++;
	}
	free_safely_str(&expanded_string);
	ft_free_tab(&split);
}
