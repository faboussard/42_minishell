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

//structure de bbuilint + options
//cd with only a relative or absolute path -> faire un strjoin
//&& transform_to_token->content + 1 == "-n" ->faire un strjoin

#include "lexer.h"
#include "general.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "../libft/inc/libft.h"
#include "error.h"

void define_token(enum e_token_type type, enum e_token_builtin builtin, enum e_token_operators operator, t_token *new_token)
{
	new_token->e_type = type;
	new_token->e_builtin = builtin;
	new_token->e_operator = operator;
}

void cpy_string_builtin(char builtins[7][10])
{
	ft_strcpy(builtins[LS], "ls");
	ft_strcpy(builtins[ECHO], "echo");
	ft_strcpy(builtins[CD], "cd");
	ft_strcpy(builtins[PWD], "pwd");
	ft_strcpy(builtins[EXIT], "exit");
	ft_strcpy(builtins[ENV], "env");
	ft_strcpy(builtins[EXPORT], "export");
	ft_strcpy(builtins[UNSET], "unset");
}

bool	define_builtin(t_token *new_token, char *string)
{
	int		i;
	char	builtins[8][10];

	cpy_string_builtin(builtins);
	i = 0;
	while (i < 8)
	{
		if (!ft_strncmp(string, builtins[i], ft_strlen(string)))
		{
			define_token(COMMAND, i, 0, new_token);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

void cpy_string_operator(char operator[7][10])
{
	ft_strcpy(operator[OPEN_PARENTHESES], "(");
	ft_strcpy(operator[CLOSE_PARENTHESES], ")");
	ft_strcpy(operator[PIPE], "|");
	ft_strcpy(operator[INPUT_REDIRECT], ">");
	ft_strcpy(operator[OUTPUT_REDIRECT], "<");
	ft_strcpy(operator[HERE_DOC], ">>");
	ft_strcpy(operator[DOUBLE_QUOTE], "\"");
	ft_strcpy(operator[SINGLE_QUOTE], "'");
}

bool	define_operator(t_token *new_token, char *string)
{
	int		i;
	char	operator[9][10];

	i = 0;
	cpy_string_operator(operator);
	while (i < 8)
	{
		if (!ft_strncmp(string, operator[i], ft_strlen(string)))
		{
			define_token(OPERATOR, 0, i, new_token);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

void create_token_to_list(t_node **tokens, t_token *new_token, char *string)
{
	t_node	*new_node;
	void	*content;

	if (string == NULL)
		return;
	if (string[0] == '-')
		define_token(ARGUMENT, 0, 0, new_token);
	if (define_builtin(new_token, string) == FALSE
		&& define_operator(new_token, string) == FALSE && string[0] != '-')
		define_token(COMMAND, 0, 0, new_token);
	content = new_token;
	new_node = ft_lstnew(content);
	if (new_node == NULL)
	{
		ft_lstclear(&new_node, &free);
		return;
	}
	ft_lstadd_back(tokens, new_node);
}

//a mettre dans parser
// fonction redefine from position in chain list.

void print_list(t_node *list_tokens)
{
	t_node  *iterator;
	t_token *token;

	iterator = list_tokens;
	while (iterator != NULL)
	{
		token = (t_token *)(iterator)->content;
		printf("Type: %d, Builtin: %d, Operator: %d\n", token->e_type, token->e_builtin, token->e_operator);
		iterator = iterator->next;
	}
}


void transform_to_token(char *string, t_node **list_tokens)
{
	int 	i;
	t_token	*token;

	//ajouter une condition pour faire le split que sil ny a pas despace avec des guillets. sinon on retirera ce token avant de resplit.
	char	**split;

	split = ft_split(string, ' ');
	if (split == NULL)
		return;
	i = 0;
	while (split[i])
	{
		token = malloc(sizeof(t_token));
		ft_memset(token, 0, sizeof(t_token));
		create_token_to_list(list_tokens, token, split[i]);
		i++;
	}
	ft_free_split(split);
	print_list(*list_tokens);
}



