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

size_t count_letters_until_pipe(t_token *head)
{
	size_t		num_commands;
	t_token     *iterator;

	num_commands = 0;
    iterator = head;
    while (iterator && iterator->e_operator != PIPE)
	{
        if (iterator->e_type == COMMAND || iterator->e_type == ARGUMENT)
			num_commands += ft_strlen(iterator->name);
        iterator = iterator->next;
	}
	return (num_commands);
}

size_t count_cmds_until_pipe(t_token *head)
{
	size_t		num_commands;
	t_token	*iterator;

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

size_t total_commands(t_token *head)
{
    size_t	num_commands;
    t_token *iterator;

    num_commands = 0;
    iterator = head;
    while (iterator && iterator->e_operator == PIPE)
    {
        num_commands++;
    }
    return (num_commands);
}