/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/27 10:16:39 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "utils.h"

char	*expand_sign(char *string, char *temp)
{
	char	*new_string;

	while (*string && *string != '=')
		string++;
	new_string = ft_strjoin(temp, string);
	if (new_string == NULL)
		exit_msg(NULL, "Malloc failed at expand_sign", ENOMEM);
	return (new_string);
}

void	erase_dollar_operator(t_token_list **iterator)
{
	if ((*iterator)->e_operator == DOLLAR)
		(*iterator)->e_operator = 0;
	(*iterator)->is_quoted_delimiter = true;
	(*iterator) = (*iterator)->next;
}

void	handle_delimitor(t_token_list **iterator)
{
	*iterator = (*iterator)->next;
	while ((*iterator) && (*iterator)->e_operator == IS_SPACE)
		(*iterator) = (*iterator)->next;
	while ((*iterator) && (*iterator)->next
		&& (*iterator)->e_operator != IS_SPACE)
	{
		if ((*iterator)->e_operator == DOLLAR)
			(*iterator)->e_operator = 0;
		while ((*iterator) && ((*iterator)->e_operator == DOUBLE_QUOTE
				|| (*iterator)->e_operator == SINGLE_QUOTE))
		{
			(*iterator)->is_quoted_delimiter = true;
			(*iterator) = (*iterator)->next;
			while ((*iterator) && (*iterator)->e_operator != DOUBLE_QUOTE
				&& (*iterator)->e_operator != SINGLE_QUOTE)
			{
				(*iterator)->is_quoted_delimiter = true;
				(*iterator) = (*iterator)->next;
			}
		}
		if ((*iterator))
			erase_dollar_operator(iterator);
	}
}

void	change_to_status(t_minishell *minishell, t_token_list *iterator)
{
	if (join_tokens(&iterator) == MALLOC_FAILED)
		exit_msg(minishell, "join_tokens", ENOMEM);
	free_safely_str(&(iterator->name));
	iterator->name = ft_itoa(minishell->status);
	if (iterator->name == NULL)
		exit_msg(minishell, "Malloc failed at expander", ENOMEM);
}

char	*expand_sigil(char *string, t_minishell *m)
{
	char	*final_string;

	if (ft_isdigit(*string))
	{
		final_string = ft_strdup(string + 1);
		if (final_string == NULL)
			exit_msg(m, "Malloc failed at expand_sigil", ENOMEM);
	}
	else
		final_string = identify_envp_string(string, m);
	return (final_string);
}
