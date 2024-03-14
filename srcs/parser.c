/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lexer.h"
#include "general.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../libft/inc/libft.h"


//a mettre dans parser
// fonction redefine from position in chain list.

int check_syntax(t_node *list_tokens)
{
	size_t	open_parentheses;
	size_t	close_parentheses;
	t_node	*iterator;
	t_token	*token;

	open_parentheses = 0;
	close_parentheses = 0;
	iterator = list_tokens;
	while (iterator != NULL)
	{
		token = (t_token *)(list_tokens)->content;
		open_parentheses += token->e_operator == OPEN_PARENTHESES;
		close_parentheses += token->e_operator == CLOSE_PARENTHESES;
		if (close_parentheses > open_parentheses)
			return (print_operator_syntax_error(token), -1);
		iterator = iterator->next;
	}
	return (close_parentheses == open_parentheses);
}

void command_to_end_word(t_node *list_tokens)
{
	t_node  *iterator;
	t_token *token;
	t_token *next_token;

	iterator = list_tokens;
	while (iterator->next != NULL)
	{
		token = (t_token *)(list_tokens)->content;
		next_token = (t_token *)(iterator->next)->content;
		if (token->e_operator == HERE_DOC)
			next_token->e_type = END_WORD;
		iterator = iterator->next;
	}
}

void arg_to_command(t_node *list_tokens)
{
	t_token	*first_token;

	first_token = (t_token *)(list_tokens)->content;
	if (first_token->e_type == ARGUMENT)
		first_token->e_type = COMMAND;
}

void requalification(t_node *list_tokens)
{
	arg_to_command(list_tokens);
	check_syntax(list_tokens);
	command_to_end_word(list_tokens);
	//ajouter une condition pour faire le split que sil ny a pas despace avec des guillets. sinon on retirera ce token avant de resplit.
}



