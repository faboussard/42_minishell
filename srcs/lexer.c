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

void	define_builtin(t_token *new_token, char *string)
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
	}
}

void	define_operator(t_token *new_token, char *string)
{
	int		i;
	char	operator[8][10];

	i = 0;
	ft_strcpy(operator[OPEN_PARENTHESES], "(");
	ft_strcpy(operator[CLOSE_PARENTHESES], ")");
	ft_strcpy(operator[PIPE], "|");
	ft_strcpy(operator[INPUT_REDIRECT], ">");
	ft_strcpy(operator[OUTPUT_REDIRECT], "<");
	ft_strcpy(operator[HERE_DOC], ">>");
	ft_strcpy(operator[DOUBLE_QUOTE], """");
	ft_strcpy(operator[SINGLE_QUOTE], "''");
	while (i++ < 8)
	{
		if (!ft_strncmp(string, operator[i], ft_strlen(string)))
			define_token(OPERATOR, 0, i, new_token);
	}
}

//static bool	define_arg(t_token *new_token, char *string)
//{
//	if (string[0] == '-')
//	{
//		new_token->t_type.e_type = ARGUMENT;
//		return (TRUE);
//	}
//	return (FALSE);
//}

void create_token(t_node **tokens, t_token *new_token, char *string)
{
	t_node	*new_node;

	define_builtin(new_token, string);
	define_operator(new_token, string);
	new_node = ft_lstnew(new_token);
	if (new_node == NULL)
	{
		free(new_token);
		return;
	}
	ft_lstadd_back(tokens, new_node);
}



void print_list(t_node *list_tokens)
{
	t_node* iterator = list_tokens;
	while (iterator != NULL)
	{
		t_token *token;

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
		printf("Type: %d, Builtin: %d, Operator: %d\n", token->e_type, token->e_builtin, token->e_operator);
		i++;
	}
	print_list(list_tokens);
}



