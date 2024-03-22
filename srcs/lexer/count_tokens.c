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

size_t count_letters_until_pipe_or_redirect(t_node *head)
{
	size_t		num_commands;
	t_node	*current;
	t_token	*token;

	num_commands = 0;
	current = head;
	while (current)
	{
		token = (t_token *) (current)->content;
		if (token->e_operator != PIPE && !is_redirect_token(token))
			num_commands += ft_strlen(token->name);
		else
			break ;
		current = current->next;
	}
	return (num_commands);
}

size_t count_cmds_until_pipe_or_redirect(t_node *head)
{
	size_t		num_commands;
	t_node	*current;
	t_token	*token;

	num_commands = 0;
	current = head;
	while (current)
	{
		token = (t_token *) (current)->content;
		if (token->e_operator != PIPE && !is_redirect_token(token))
			num_commands ++;
		else
			break ;
		current = current->next;
	}
	return (num_commands);
}