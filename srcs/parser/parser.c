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
#include "utils.h"
#include "parser.h"
#include <stdlib.h>

//int check_parentheses(t_token *list_tokens)
//{
//	size_t	open_parentheses;
//	size_t	close_parentheses;
//	t_token	*iterator;
//	t_token	*token;
//
//	open_parentheses = 0;
//	close_parentheses = 0;
//	iterator = list_tokens;
//	while (iterator != NULL)
//	{
//		token = (t_token *)(iterator)->value;
//		open_parentheses += token->e_operator == OPEN_PARENTHESES;
//		close_parentheses += token->e_operator == CLOSE_PARENTHESES;
//		iterator = iterator->next;
//	}
//	if (close_parentheses > open_parentheses)
//		return (print_operator_syntax_error(token), -1);
//	if (open_parentheses > close_parentheses)
//		return (print_operator_syntax_error(token), -1);
//	return (close_parentheses == open_parentheses);
//}


//int check_syntax_with_tokens(t_token *list_tokens)
//{
//	if (check_parentheses(list_tokens) == -1)
//		exit(EXIT_FAILURE);
//	return (0);
//}


//void to_subshell(t_token *list_tokens)
//{
//	t_token *iterator;
//	t_token *token;
//	t_token *next_token;
//
//	iterator = list_tokens;
//	while (iterator->next != NULL)
//	{
//		token = (t_token *)(iterator)->content;
//		next_token = (t_token *)(iterator->next)->content;
//		if (token->e_operator == OPEN_PARENTHESES && next_token->e_type == COMMAND)
//			next_token->e_type = SUBSHELL;
//		iterator = iterator->next;
//	}
//}

void arg_to_command(t_token *list_tokens)
{
	t_token  *iterator;
	t_token *next_token;

	if (ft_lstsize(list_tokens) == 2)
	{
		if (list_tokens->e_type == ARGUMENT)
            list_tokens->e_type = COMMAND;
	}
	else
	{
		iterator = list_tokens;
		while (iterator->next != NULL)
		{
			next_token = iterator->next;
			if (iterator->e_type == COMMAND && next_token->e_type != OPERATOR && next_token->e_type != PATH_FILE)
				next_token->e_type = ARGUMENT;
			if (iterator->e_type == PATH_FILE)
				next_token->e_type = COMMAND;
			iterator = iterator->next;
		}
	}
}

void change_type_to_file(t_token *list_tokens)
{
	t_token *iterator;
	t_token *next_token;

	iterator = list_tokens;
	while (iterator->next != NULL)
	{
		next_token = iterator->next;
		if (is_redirect_token(iterator))
			next_token->e_type = PATH_FILE;
		iterator = iterator->next;
	}
}

void token_requalification(t_token *list_tokens)
{
	change_type_to_file(list_tokens);
	arg_to_command(list_tokens);
//	to_subshell(list_tokens);
}
