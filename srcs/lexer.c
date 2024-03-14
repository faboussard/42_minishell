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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                               		        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/22 12:10:15 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//structure de bbuilint + options
//cd with only a relative or absolute path -> faire un strjoin
//&& new_token->content + 1 == "-n" ->faire un strjoin

#include "lexer.h"
#include "general.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "../libft/inc/libft.h"

void define_token(enum e_token_type type, enum e_token_builtin builtin, enum e_token_operators operator, t_token *new_token)
{
	new_token->e_type = type;
	new_token->e_builtin = builtin;
	new_token->e_operator = operator;
}

bool	define_builtin(t_token *new_token, char *string)
{
	int		i;
	char	builtins[8][10];

	ft_strcpy(builtins[LS], "ls");
	ft_strcpy(builtins[ECHO], "echo");
	ft_strcpy(builtins[CD], "cd");
	ft_strcpy(builtins[PWD], "pwd");
	ft_strcpy(builtins[EXIT], "exit");
	ft_strcpy(builtins[ENV], "env");
	ft_strcpy(builtins[EXPORT], "export");
	ft_strcpy(builtins[UNSET], "unset");
	i = 0;
	while (i++ < 8)
	{
		if (!ft_strncmp(string, builtins[i], ft_strlen(string)))
			define_token(COMMAND, i, 0, new_token);
		return (TRUE);
	}
	return (FALSE);
}

void cpy_string_operator(char operator[9][10])
{
	ft_strcpy(operator[0], "cd");
	ft_strcpy(operator[1], "ls");
	ft_strcpy(operator[2], "echo");
	ft_strcpy(operator[3], "pwd");
	ft_strcpy(operator[4], "exit");
	ft_strcpy(operator[5], "env");
	ft_strcpy(operator[6], "export");
	ft_strcpy(operator[7], "unset");
	ft_strcpy(operator[8], "|");
}

bool	define_operator(t_token *new_token, char *string)
{
	int		i;
	char	operator[9][10];

	i = 0;
	cpy_string_operator(operator);
	while (i++ < 9)
	{
		if (!ft_strncmp(string, operator[i], ft_strlen(string)))
			define_token(OPERATOR, 0, i, new_token);
		return (TRUE);
	}
	return (FALSE);
}

static bool	define_arg(t_token *new_token, char *string)
{
	if (string[0] == '-')
	{
		define_token(ARGUMENT, 0, 0, new_token);
		return (TRUE);
	}
	return (FALSE);
}

void create_token(t_node **tokens, t_token *new_token, char *string)
{
	t_node	*new_node;

	if (define_builtin(new_token, string) == FALSE
		|| define_operator(new_token, string) == FALSE)
		define_token(COMMAND, 0, 0, new_token);
	new_node = ft_lstnew(new_token);
	if (new_node == NULL)
	{
		free(new_token);
		return;
	}
	ft_lstadd_back(tokens, new_node);
}

//a mettre dans parser
// fonction redefine from position in chain list.
void redefine_to_argument(t_node *list_tokens)
{
	t_node  *iterator;
	t_token *token;
	t_token *token_next;

	iterator = list_tokens;
	token = (t_token *)(iterator)->content;
	token_next = (t_token *)(iterator)->next->content;
	while (iterator->next != NULL)
	{
		if (token_next->e_type == COMMAND && token_next->e_operator == OPTION && token->e_type == COMMAND)
			token_next->e_type = ARGUMENT;
		iterator = iterator->next;
	}
}

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


void new_token( char *string)
{
	int 	i;
	t_token	*token;
	t_node 	*list_tokens;
	//ajouter une condition pour faire le split que sil ny a pas despace avec des guillets. sinon on retirera ce token avant de resplit.
	char	**split;

	list_tokens = NULL;
	split = ft_split(string, ' ');
	if (split == NULL)
		return;

	i = 0;
	while (split[i])
	{
		token = malloc(sizeof(t_token));
		ft_memset(token, 0, sizeof(t_token));
		create_token(&list_tokens, token, split[i]);
		i++;
	}
	print_list(list_tokens);
}



