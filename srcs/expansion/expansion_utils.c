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
	return (string);
}

void handle_delimitor(t_token_list *iterator)
{
	iterator = iterator->next;
	while (iterator && iterator->e_operator == IS_SPACE)
		iterator = iterator->next;
	while (iterator && iterator->next && iterator->e_operator != IS_SPACE)
	{
		if (iterator->e_operator == DOUBLE_QUOTE || iterator->e_operator == SINGLE_QUOTE)
		{
			iterator = iterator->next;
			while (iterator && iterator->next && iterator->e_operator != DOUBLE_QUOTE &&
				   iterator->e_operator != SINGLE_QUOTE)
				iterator = iterator->next;
		}
		iterator = iterator->next;
	}
}


void change_name_to_status(t_minishell *minishell, t_token_list *iterator)
{
	join_tokens(minishell, &iterator);
	free(iterator->name);
	iterator->name = ft_itoa(minishell->status);
	if (iterator->name == NULL)
		exit_msg(minishell, "Malloc failed at expander", -1);
}
