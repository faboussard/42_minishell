/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:43:37 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/05 11:19:31 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

size_t	count_letters_until_pipe(t_token_list *head)
{
	size_t			num_commands;
	t_token_list	*iterator;

	num_commands = 0;
	iterator = head;
	while (iterator != NULL && iterator->e_operator != PIPE)
	{
		if (iterator->e_type == COMMAND || iterator->e_type == ARGUMENT)
			num_commands += ft_strlen(iterator->name);
		iterator = iterator->next;
	}
	return (num_commands);
}

int count_tokens_by_operator(t_minishell *minishell, enum e_token_operators operator_type)
{
	t_token_list	*iterator;
	int				i;

	i = 0;
	iterator = minishell->list_tokens;
	while (iterator)
	{
		if (iterator->e_operator == operator_type)
			i++;
		iterator = iterator->next;
	}
	return (i);
}

