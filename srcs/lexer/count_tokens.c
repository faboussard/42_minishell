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

size_t count_letters_until_pipe_or_redirect(t_token *head)
{
	size_t		num_commands;
	t_token     *iterator;

	num_commands = 0;
    iterator = head;
	while (iterator)
	{
		if (iterator->e_operator != PIPE && !is_redirect_token(iterator))
			num_commands += ft_strlen(iterator->name);
		else
			break ;
        iterator = iterator->next;
	}
	return (num_commands);
}

size_t count_cmds_until_pipe_or_redirect(t_token *head)
{
	size_t		num_commands;
	t_token	*iterator;

	num_commands = 0;
    iterator = head;
	while (iterator)
	{
		if (iterator->e_operator != PIPE && !is_redirect_token(iterator))
			num_commands ++;
		else
			break ;
        iterator = iterator->next;
	}
	return (num_commands);
}