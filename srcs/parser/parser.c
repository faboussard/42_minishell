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

//int check_parentheses(t_token_list *list_tokens)
//{
//	size_t	open_parentheses;
//	size_t	close_parentheses;
//	t_token_list	*iterator;
//	t_token_list	*token;
//
//	open_parentheses = 0;
//	close_parentheses = 0;
//	iterator = list_tokens;
//	while (iterator != NULL)
//	{
//		open_parentheses += iterator->e_operator == OPEN_PARENTHESES;
//		close_parentheses += iterator->e_operator == CLOSE_PARENTHESES;
//		iterator = iterator->next;
//	}
//	if (close_parentheses > open_parentheses)
//		return (print_operator_syntax_error(token), -1);
//	if (open_parentheses > close_parentheses)
//		return (print_operator_syntax_error(token), -1);
//	return (close_parentheses == open_parentheses);
//}

//void to_subshell(t_token_list *list_tokens)
//{
//	t_token_list *iterator;
//	t_token_list *token;
//	t_token_list *next_token;
//
//	iterator = list_tokens;
//	while (iterator->next != NULL)
//	{
//		next_token = iterator->next;
//		if (token->e_operator == OPEN_PARENTHESES && next_token->e_type == COMMAND)
//			next_token->e_type = SUBSHELL;
//		iterator = iterator->next;
//	}
//}

void arg_to_command(t_token_list *list_tokens)
{
	t_token_list  *iterator;
	t_token_list *next_token;

    iterator = list_tokens;
	if (ft_lstsize_token(iterator) == 1)
	{
		if (iterator->e_type == ARGUMENT)
            iterator->e_type = COMMAND;
	}
	else
	{
		while (iterator->next != NULL)
		{
			next_token = iterator->next;
			if (iterator->e_type == COMMAND && next_token->e_type != OPERATOR && next_token->e_type != IN_FILE && next_token->e_type != OUT_FILE)
				next_token->e_type = ARGUMENT;
			iterator = iterator->next;
		}
	}
}

void to_infile_or_outfile(t_token_list *list_tokens)
{
    t_token_list *iterator;
    t_token_list *next_token;

    iterator = list_tokens;
    while (iterator->next != NULL)
    {
        next_token = iterator->next;
        if (iterator->e_operator == INPUT_REDIRECT || iterator->e_operator == APPEND)
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

void token_requalification(t_token_list *list_tokens)
{
	to_infile_or_outfile(list_tokens);
	arg_to_command(list_tokens);
//	to_subshell(list_tokens);
}


char **split_user_input(t_minishell *minishell)
{
	char	**split;

	split = split_with_quotes_management(minishell->user_input);
	if (split == NULL)
		exit_msg(minishell, "Malloc failed at split for tokenization", 2);
	return (split);
}

int parse_input(t_minishell *minishell)
{
	char	**split;

	split = split_user_input(minishell);
	transform_to_token(minishell, split);
	if (check_syntax(minishell) == 1)
		return (1);
	token_requalification(minishell->list_tokens);
	expand_tokens(minishell);
	create_process_list(minishell);
	return (0);
}
