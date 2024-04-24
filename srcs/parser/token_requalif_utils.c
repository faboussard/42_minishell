/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/19 11:06:17 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "utils.h"
#include <stdlib.h>

void	arg_to_command(t_token_list *list_tokens)
{
	t_token_list	*iterator;
	t_token_list	*next_token;

	iterator = list_tokens;
	if (ft_lstsize_token(iterator) == 1)
		iterator->e_type = COMMAND;
	else
	{
		while (iterator->next != NULL)
		{
			next_token = iterator->next;
			if (iterator->e_type == COMMAND && next_token->e_type != OPERATOR
				&& next_token->e_type != IN_FILE
				&& next_token->e_type != OUT_FILE)
				next_token->e_type = ARGUMENT;
			if (iterator->e_operator == DOLLAR)
				iterator->e_type = COMMAND;
			if (iterator->e_type == ARGUMENT && next_token->e_type != OPERATOR)
				next_token->e_type = ARGUMENT;
			iterator = iterator->next;
		}
	}
}

void	to_infile_or_outfile(t_token_list *list_tokens)
{
	t_token_list	*iterator;
	t_token_list	*next_token;

	iterator = list_tokens;
	while (iterator && iterator->next != NULL)
	{
		next_token = iterator->next;
		if (iterator->e_operator == INPUT_REDIRECT)
			next_token->e_type = IN_FILE;
		if (iterator->e_operator == OUTPUT_REDIRECT)
			next_token->e_type = OUT_FILE;
		if (iterator->e_operator == HERE_DOC)
			next_token->e_type = DELIMITER;
		if (iterator->e_operator == APPEND)
			next_token->e_type = APPEND_FILE;
		iterator = iterator->next;
	}
}

void	define_builtins(t_token_list *list_tokens)
{
	t_token_list	*iterator;

	iterator = list_tokens;
	while (iterator)
	{
		get_builtin_token(iterator, iterator->name);
		iterator = iterator->next;
	}
}

void	define_operators(t_token_list *list_tokens)
{
	t_token_list	*iterator;

	iterator = list_tokens;
	while (iterator)
	{
		get_operator_token(iterator, iterator->name);
		iterator = iterator->next;
	}
}

void define_heredoc_and_append(t_minishell *minishell, t_token_list **list)
{
	t_token_list *cpy;

	if (list == NULL || *list == NULL)
		return ;
	cpy = *list;
	while (*list != NULL && (*list)->next != NULL)
	{
		if ((*list)->e_operator == INPUT_REDIRECT && (*list)->next->e_operator == INPUT_REDIRECT)
		{
			join_tokens(minishell, list);
			(*list)->e_type = OPERATOR;
			(*list)->e_operator = HERE_DOC;
		}
		if ((*list)->e_operator == OUTPUT_REDIRECT && (*list)->next->e_operator == OUTPUT_REDIRECT)
		{
			join_tokens(minishell, list);
			(*list)->e_type = OPERATOR;
			(*list)->e_operator = APPEND;
		}
		*list = (*list)->next;
	}
	*list = cpy;
}