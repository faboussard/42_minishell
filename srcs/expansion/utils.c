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

char *expand_sign(char *string, char *temp)
{
	while (*string && *string != '=')
		string++;
	string = ft_strjoin(temp, string);
	if (string == NULL)
		exit_msg_minishell(NULL, "Malloc failed at expand_sign", ENOMEM);
	return (string);
}

void treat_in_delimitor(t_token_list **iterator)
{
	if ((*iterator)->e_operator == DOLLAR)
		(*iterator)->e_operator = 0;
	(*iterator)->is_quoted_delimiter = true;
	(*iterator) = (*iterator)->next;
}

void handle_delimitor(t_token_list **iterator)
{
	*iterator = (*iterator)->next;
	while ((*iterator) && (*iterator)->e_operator == IS_SPACE)
		(*iterator) = (*iterator)->next;
	while ((*iterator) && (*iterator)->next && (*iterator)->e_operator != IS_SPACE)
	{
		if ((*iterator)->e_operator == DOLLAR)
			(*iterator)->e_operator = 0;
		while ((*iterator) && ((*iterator)->e_operator == DOUBLE_QUOTE || (*iterator)->e_operator == SINGLE_QUOTE))
		{
			(*iterator)->is_quoted_delimiter = true;
			(*iterator) = (*iterator)->next;
			while ((*iterator) && (*iterator)->e_operator != DOUBLE_QUOTE &&
					(*iterator)->e_operator != SINGLE_QUOTE)
			{
				(*iterator)->is_quoted_delimiter = true;
				(*iterator) = (*iterator)->next;
			}
		}
		if ((*iterator))
			treat_in_delimitor(iterator);
	}
}

void change_name_to_status(t_minishell *minishell, t_token_list *iterator)
{
	join_tokens(minishell, &iterator);
	free_safely_str(&(iterator->name));
	iterator->name = ft_itoa(minishell->status);
	if (iterator->name == NULL)
		exit_msg_minishell(minishell, "Malloc failed at expander", ENOMEM);
}

char *expand_sigil(char *string, t_minishell *m)
{
	char *final_string;

	if (ft_isdigit(*string))
		final_string = ft_strdup(string + 1);
	else
		final_string = identify_envp_string(string, m);
	if (final_string == NULL)
		exit_msg_minishell(m, "Malloc failed at expand_sigil", ENOMEM);
	return (final_string);
}
