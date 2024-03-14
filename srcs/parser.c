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
void redefine_to_cmd_if_first(t_node *list_tokens)
{
	t_token *token;
	t_token *token_next;

	token = (t_token *)(list_tokens)->content;
	token_next = (t_token *)(list_tokens)->next->content;
	while (list_tokens->next != NULL)
	{
		if (token_next->e_type == COMMAND && token->e_type == COMMAND)
			token_next->e_type = ARGUMENT;
		list_tokens = list_tokens->next;
	}
}


void check_syntax(t_node *list_tokens)
{
	t_node	*iterator;
	t_token	*token;

	iterator = list_tokens;
	while (iterator != NULL)
	{
		token = (t_token *)(list_tokens)->content;
		print_operator_syntax_error(token);
		iterator = iterator->next;
	}
}

void parse(t_node *list_tokens)
{
	int 	i;
	t_token	*first_token;

	first_token = (t_token *)(list_tokens)->content;
	if (first_token->e_type == ARGUMENT)
		first_token->e_type = COMMAND;
	check_syntax(list_tokens);
	//ajouter une condition pour faire le split que sil ny a pas despace avec des guillets. sinon on retirera ce token avant de resplit.
}



