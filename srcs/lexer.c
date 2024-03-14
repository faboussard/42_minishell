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

void create_token_to_list(t_node **tokens, t_token *new_token, char *string)
{
	t_node	*new_node;
	void	*content;

	if (string == NULL)
		return;
	if (string[0] == '-')
		define_token(ARGUMENT, NO_OPERATOR, NO_BUILTIN, new_token);
	if (define_builtin(new_token, string) == FALSE
		&& define_operator(new_token, string) == FALSE && string[0] != '-')
		define_token(COMMAND, NO_OPERATOR, NO_BUILTIN, new_token);
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
}



