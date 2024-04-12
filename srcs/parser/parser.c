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

size_t check_quotes(t_minishell *minishell)
{
	size_t	quote;
	t_token_list	*iterator;

	quote = 0;
	iterator = minishell->list_tokens;
	while (iterator != NULL)
	{
		if (iterator->e_operator == DOUBLE_QUOTE || iterator->e_operator == SINGLE_QUOTE)
			quote ++;
		iterator = iterator->next;
	}
	if (quote % 2 != 0)
		return (print_error("unclosed quote"), 1);
	return (0);
}

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
			if (iterator->e_operator == DOLLAR)
				iterator->e_type = COMMAND;
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

void token_requalification(t_token_list *list_tokens)
{
	to_infile_or_outfile(list_tokens);
	arg_to_command(list_tokens);
}

void check_sequence_dollar_followed_by_quotes(char *user_input)
{
	size_t	i;
	i = 0;

	while (user_input[i + 1] != '\0')
	{
		if (user_input[i] == '$' && user_input[i + 1] == '\"')
		{
			ft_memcpy(&user_input[i], &user_input[i + 1], ft_strlen(user_input - 1));
		}
		i++;
	}
}

int parse_input(t_minishell *minishell)
{
	char *string;

//	check_sequence_dollar_followed_by_quotes(minishell->user_input);
	string = minishell->user_input;
	transform_to_token(minishell, string);
	if (check_syntax(minishell) == 1)
		return (1);
	expander(minishell);
	handler_join_tokens(minishell, &minishell->list_tokens);
	deal_double_double_quotes_or_double_single_quotes(minishell->user_input);
//	remove_quotes(minishell, minishell->list_tokens);

//PARSING A PARTIR DICI
	token_requalification(minishell->list_tokens);
	create_envp_table(minishell);
	create_process_list(minishell);
	return (0);
}
