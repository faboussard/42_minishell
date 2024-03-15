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

int check_parentheses(t_node *list_tokens)
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
		token = (t_token *)(iterator)->content;
		open_parentheses += token->e_operator == OPEN_PARENTHESES;
		close_parentheses += token->e_operator == CLOSE_PARENTHESES;
		iterator = iterator->next;
	}
	if (close_parentheses > open_parentheses)
		return (print_operator_syntax_error(token), -1);
	if (open_parentheses > close_parentheses)
		return (print_operator_syntax_error(token), -1);
	return (close_parentheses == open_parentheses);
}


int check_syntax_with_tokens(t_node *list_tokens)
{
	if (check_parentheses(list_tokens) == -1)
		exit(EXIT_FAILURE);
	return (0);
}

void create_subtype_end_word(t_node *list_tokens)
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
			next_token->e_subtype = END_WORD;
		iterator = iterator->next;
	}
}

void give_subtype(t_node *list_tokens)
{
	t_token *next_token;
	t_node *iterator;

	iterator = list_tokens;
	while (iterator->next != NULL)
	{
		next_token = (t_token *)(iterator->next)->content;
		next_token->e_subtype = SUBSHELL;
		iterator = iterator->next;
	}
}

void create_subtype_for_groups(t_node *list_tokens)
{
	t_node *iterator;
	t_token *token;
	t_token *last_token;

	iterator = list_tokens;
	while (iterator->next != NULL)
	{
		token = (t_token *)(list_tokens)->content;
		last_token = return_last_token(list_tokens);
		if (token->e_operator == OPEN_PARENTHESES && last_token->e_operator == CLOSE_PARENTHESES)
			give_subtype(list_tokens);
		iterator = iterator->next;
	}
}

void create_subtype_subshell(t_node *list_tokens)
{
	t_node *iterator;
	t_token *token;
	t_token *next_token;

	iterator = list_tokens;
	while (iterator->next != NULL)
	{
		token = (t_token *)(list_tokens)->content;
		next_token = (t_token *)(iterator->next)->content;
		if (token->e_operator == OPEN_PARENTHESES && next_token->e_type == COMMAND)
			next_token->e_subtype = SUBSHELL;
		iterator = iterator->next;
	}
	create_subtype_for_groups(list_tokens);
}

void token_with_subtype(t_node *list_tokens)
{
	create_subtype_end_word(list_tokens);
	create_subtype_subshell(list_tokens);
}

void arg_to_command(t_node *list_tokens)
{
	t_token *first_token;
	t_node  *iterator;
	t_token *token;
	t_token *next_token;

	first_token = (t_token *) (list_tokens)->content;
	if (first_token->e_type == ARGUMENT)
		first_token->e_type = COMMAND;
	iterator = list_tokens;
	while (iterator->next != NULL)
	{
		token = (t_token *)(list_tokens)->content;
		next_token = (t_token *)(iterator->next)->content;
		if (token->e_subtype == END_WORD)
			next_token->e_type = COMMAND;
		iterator = iterator->next;
	}
}

void token_requalification(t_node *list_tokens)
{
	arg_to_command(list_tokens);
}

void token_rework(t_node *list_tokens)
{
	check_syntax_with_tokens(list_tokens);
	token_requalification(list_tokens);
	token_with_subtype(list_tokens);
	//ajouter une condition pour faire le split que sil ny a pas despace avec des guillets. sinon on retirera ce token avant de resplit.
}



