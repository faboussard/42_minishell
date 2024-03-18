/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "../libft/inc/libft.h"
#include "error.h"
#include "parser.h"

int check_string_syntax(char *string)
{
	int i;
	int count;

	count = 0;
	i = 0;
	if (string == NULL)
		return (-1);
	if (parentheses_error(string) == -1 || parentheses_on_arg(string) == -1)
		exit(EXIT_FAILURE);
	while (string[i])
	{
		if (*string == 32)
			count++;
		i++;
	}
	if (count == ft_strlen(string))
		return (-1);
	return (0);
}

void
define_token(enum e_token_type type, enum e_token_builtin builtin, enum e_token_operators operator, t_token *new_token)
{
	new_token->e_type = type;
	new_token->e_builtin = builtin;
	new_token->e_operator = operator;
}

void create_token_to_list(t_node **tokens, t_token *new_token, char *string)
{
	t_node *new_node;
	void *content;

	if (string == NULL)
		return;
	if (string[0] == '-')
		define_token(ARGUMENT, NO_BUILTIN, NO_OPERATOR, new_token);
	if (string[0] == '(')
	{
		define_token(COMMAND, NO_BUILTIN, OPEN_PARENTHESES, new_token);
		new_token->e_type = SUBSHELL;
	}
	if (get_builtin_token(new_token, string) == FALSE
		&& get_operator_token(new_token, string) == FALSE && string[0] != '-')
		define_token(COMMAND, NO_BUILTIN, NO_OPERATOR, new_token);
	content = new_token;
	new_node = ft_lstnew(content);
	if (new_node == NULL)
	{
		ft_lstclear(&new_node, &free);
		return;
	}
	ft_lstadd_back(tokens, new_node);
}

void transform_to_token(char **string, t_node **list_tokens)
{
	int i;
	t_token *token;

	i = 0;
	while (string[i])
	{
		if (check_string_syntax(string[i]) == -1)
			return;
		string[i] = manage_quotes(string[i]);
		token = malloc(sizeof(t_token));
		ft_memset(token, 0, sizeof(t_token));
		create_token_to_list(list_tokens, token, string[i]);
		i++;
	}
}

t_node *get_list_tokens(char **string)
{
	t_node *list_tokens;

	list_tokens = NULL;
	transform_to_token(string, &list_tokens);
	token_rework(list_tokens);
	return (list_tokens);
}



