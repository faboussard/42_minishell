/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
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

void define_token(t_minishell *minishell, t_token *new_token, char *string)
{
	new_token->name = ft_strdup(string);
	if (new_token->name == NULL)
		exit_msg(minishell, "Malloc failed at tokenization for name", 2);
	new_token->next = NULL;
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

t_token	*ft_lstlast_token(t_token *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void add_token_to_list(t_token **tokens, t_token *new_token)
{
	t_token	*last;

	if (*tokens != NULL)
	{
		last = ft_lstlast_token((t_token *)(*tokens));
		if (last != NULL)
			last->next = new_token;
	}
	else
		*tokens = new_token;	
}

int transform_to_token(t_minishell *minishell, t_token **list_tokens)
{
	int 	i;
	t_token	*new_token;
	char	**split;

	i = 0;
	split = split_with_quotes_management(minishell->user_input);
	if (split == NULL)
		return (0);
	new_token = NULL;
	while (split[i])
	{
		new_token = malloc(sizeof(t_token));
		if (new_token == NULL)
			exit_msg(minishell, "Malloc failed at tokenization", 2);
		define_token(minishell, new_token, split[i]);
		add_token_to_list(list_tokens, new_token);
		i++;
	}
	ft_free_all_tab(split);
	return (1);
}

t_token *parse_input(t_minishell *minishell)
{
	t_token	*list_tokens;

	list_tokens = NULL;
	if (!transform_to_token(minishell, &list_tokens))
		return (NULL);
	//	check_syntax_with_tokens(list_tokens);
	token_requalification(list_tokens);
	return (list_tokens);
}
