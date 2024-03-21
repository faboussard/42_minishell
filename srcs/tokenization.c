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
#include "parser.h"

void define_token_types(enum e_token_type type, enum e_token_builtin builtin, enum e_token_operators operator, t_token *new_token)
{
	new_token->e_type = type;
	new_token->e_builtin = builtin;
	new_token->e_operator = operator;
}

void add_token_to_list(t_node **tokens, t_token *new_token)
{
	t_node *new_node;
	void	*content_node;

	content_node = new_token;
	new_node = ft_lstnew(content_node);
	if (new_node == NULL)
	{
		free_token(content_node);
		ft_lstclear(&new_node, (void *) free_token);
		return;
	}
	ft_lstadd_back(tokens, new_node);
}

void define_token(t_token *new_token, char *string)
{
	if (string == NULL)
		return;
	new_token->name = ft_strdup(string);
	if (new_token->name == NULL)
		return ;
	if (string[0] == '-')
		define_token_types(ARGUMENT, NO_BUILTIN, NO_OPERATOR, new_token);
	if (string[0] == '(')
	{
		define_token_types(COMMAND, NO_BUILTIN, OPEN_PARENTHESES, new_token);
		new_token->e_type = SUBSHELL;
	}
	if (get_builtin_token(new_token, string) == FALSE
		&& get_operator_token(new_token, string) == FALSE && string[0] != '-')
		define_token_types(COMMAND, NO_BUILTIN, NO_OPERATOR, new_token);
}

void transform_to_token(char *string, t_node **list_tokens)
{
	int 	i;
	t_token	*token;
	char	**split;

	i = 0;
	split = split_with_quotes_management(string);
	if (split == NULL)
		return ;
	while (split[i])
	{
		token = malloc(sizeof(t_token));
		ft_memset(token, 0, sizeof(t_token));
		define_token(token, split[i]);
		add_token_to_list(list_tokens, token);
		i++;
	}
	ft_free_all_tab(split);
}

t_node *get_list_tokens(char *string)
{
	t_node *list_tokens;

	list_tokens = NULL;
	transform_to_token(string, &list_tokens);
	token_rework(list_tokens);
	return (list_tokens);
}
