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

void define_token_types(enum e_token_type type, enum e_token_builtin builtin, enum e_token_operators operator, t_token_list *new_token)
{
	new_token->e_type = type;
	new_token->e_builtin = builtin;
	new_token->e_operator = operator;
}

int define_token(t_token_list *new_token, char *string)
{
	new_token->name = ft_strdup(string);
	if (new_token->name == NULL)
		return 0;
	new_token->next = NULL;
	if (string[0] == '-')
		define_token_types(ARGUMENT, NO_BUILTIN, NO_OPERATOR, new_token);
	if (get_builtin_token(new_token, string) == FALSE
		&& get_operator_token(new_token, string) == FALSE && string[0] != '-')
		define_token_types(COMMAND, NO_BUILTIN, NO_OPERATOR, new_token);
	return (1);
}

t_token_list	*ft_lstlast_token(t_token_list *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void add_token_to_list(t_token_list **list_tokens, t_token_list *new_token)
{
	t_token_list	*last;

	if (*list_tokens != NULL)
	{
		last = ft_lstlast_token(*list_tokens);
		if (last != NULL)
			last->next = new_token;
	}
	else
		*list_tokens = new_token;
}

void check_syntax(t_token_list *list_tokens)
{
	t_token_list *iterator;
	t_token_list *next_token;

	if (list_tokens != NULL)
	{
		iterator = list_tokens;
		while (iterator != NULL && iterator->next != NULL)
		{
			next_token = iterator->next;
			if (iterator->e_type == OPERATOR && next_token->e_type == OPERATOR)
			{
				print_operator_syntax_error(iterator->next);
				free_minishell(list_tokens);
				exit(1);
			}
			iterator = iterator->next;
		}
	}
}

void transform_to_token(t_minishell *minishell)
{
	int 			i;
	t_token_list	*new_token;
	char			**split;

	i = 0;
	split = split_with_quotes_management(minishell->user_input);
	if (split == NULL)
		exit_msg(minishell, "Malloc failed at split for tokenization", 2);
	while (split[i])
	{
		new_token = malloc(sizeof(t_token_list));
		if (new_token == NULL)
		{
			ft_free_all_tab(split);
			exit_msg(minishell, "Malloc failed at tokenization", 2);
		}
		if (!define_token(new_token, split[i]))
		{
			free(new_token);
			ft_free_all_tab(split);
			exit_msg(minishell, "Malloc failed at tokenization", 2);
		}
		add_token_to_list(&minishell->list_tokens, new_token);
		i++;
	}
	ft_free_all_tab(split);
}

void parse_input(t_minishell *minishell)
{
	transform_to_token(minishell);
	check_syntax(minishell->list_tokens);
	token_requalification(minishell->list_tokens);
}
