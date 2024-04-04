/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:43:37 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/19 09:43:37 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include "parser.h"

size_t count_letters_until_pipe(t_token_list *head)
{
	size_t		num_commands;
	t_token_list     *iterator;

	num_commands = 0;
    iterator = head;
    while (iterator != NULL&& iterator->e_operator != PIPE)
	{
        if (iterator->e_type == COMMAND || iterator->e_type == ARGUMENT)
			num_commands += ft_strlen(iterator->name);
        iterator = iterator->next;
	}
	return (num_commands);
}

size_t count_cmds_until_pipe(t_token_list *head)
{
	size_t		num_commands;
	t_token_list	*iterator;

	num_commands = 0;
    iterator = head;
	while (iterator && iterator->e_operator != PIPE)
	{
		if (iterator->e_type == COMMAND || iterator->e_type == ARGUMENT)
			num_commands++;
        iterator = iterator->next;
	}
	return (num_commands);
}

void count_total_commands(t_minishell *minishell)
{
    t_token_list *iterator;

	minishell->total_commands = 1;
    iterator = minishell->list_tokens;
    while (iterator && iterator->e_operator == PIPE)
	{
		minishell->total_commands++;
		iterator = iterator->next;
	}
}