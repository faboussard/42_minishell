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


//ETAPES
//1. TOUT TOKENIZER
//2. EXPAND
//3. ENLEVER LES DOUBLES QUOTES
//4. ENLEVER LES ESPACES

void define_token_types(enum e_token_type type, enum e_token_builtin builtin, enum e_token_operators operator,
						t_token_list *new_token)
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
	if (get_builtin_token(new_token, string) == FALSE
		&& get_operator_token(new_token, string) == FALSE)
		define_token_types(COMMAND, NO_BUILTIN, NO_OPERATOR, new_token);
	return (1);
}

char find_sep(char c)
{
	if (c == ' ' || c == '\t')
		return (' ');
	if (c == '\'')
		return ('\'');
	if (c == '\"')
		return ('\"');
	if (c == '$')
		return ('\"');
	return (0);
}

void join_double_quotes(t_minishell *minishell, t_token_list **list)
{
	char *joined_name;
	t_token_list *t2;
	t_token_list *t1;

	t1 = (*list);
	t2 = (*list)->next;
	joined_name = ft_strjoin(t1->name, t2->name);
	free(t1->name);
	t1->name = ft_strdup(joined_name);
	free(joined_name);
	if (t1->name == NULL)
		exit_msg(minishell, "Malloc failed at tokenization", 1);
	define_token_types(COMMAND, NO_BUILTIN, NO_OPERATOR, (t1));
	t1->next = t2->next;
	free_token(t2);
	t1 = t1->next;
}

void join_tokens(t_minishell *minishell, t_token_list **list)
{
	t_token_list *cpy;

	cpy = (*list);
	while ((*list) != NULL)
	{
		if ((*list)->next != NULL && (*list)->e_operator == DOUBLE_QUOTE)
		{
			join_double_quotes(minishell, &minishell->list_tokens);
			while ((*list)->next != NULL && (*list)->next->e_operator != DOUBLE_QUOTE)
				join_double_quotes(minishell, list);
			join_double_quotes(minishell, list);
			(*list) = (*list)->next;
		} else
			(*list) = (*list)->next;
	}
	*list = cpy;
}

void create_token(t_minishell *minishell, char *string)
{
	t_token_list *new_token;

	new_token = ft_calloc(1, sizeof(t_token_list));
	if (new_token == NULL)
	{
		free(string);
		exit_msg(minishell, "Malloc failed at tokenization", 2);
	}
	if (!define_token(new_token, string))
	{
		free(string);
		free(new_token);
		exit_msg(minishell, "Malloc failed at tokenization", 2);
	}
	add_token_to_list(&minishell->list_tokens, new_token);
}

void transform_to_token(t_minishell *minishell, char *string)
{
	int i;
	char *temp;
	char c;
	int j;

	i = 0;
	while (string[i])
	{
		temp = ft_calloc(1, ft_strlen(string) + 1);
		if (find_sep(string[i]))
		{
			temp[0] = string[i];
			temp[1] = '\0';
			create_token(minishell, temp);
			i++;
		} else if (string[i])
		{
			j = i;
			while (string[j] && find_sep(string[j]) == 0)
				j++;
			c = find_sep(string[j]);
			temp = add_until_char(temp, string, &i, c);
			create_token(minishell, temp);
			i++;
		}
		if (temp)
		{
			free(temp);
			temp = NULL;
		}
	}
}
