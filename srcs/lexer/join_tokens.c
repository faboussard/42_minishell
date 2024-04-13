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

void join_tokens(t_minishell *minishell, t_token_list **list)
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

void in_dquotes_join_tokens(t_minishell *minishell, t_token_list **list)
{
	t_token_list *cpy;

	cpy = (*list);
	while ((*list) != NULL)
	{
		if ((*list)->next != NULL && (*list)->e_operator == DOUBLE_QUOTE)
		{
			(*list) = (*list)->next;
			while ((*list)->next != NULL && (*list)->next->e_operator != DOUBLE_QUOTE)
				join_tokens(minishell, list);
			(*list) = (*list)->next;
		}
		else
			(*list) = (*list)->next;
	}
	*list = cpy;
}

void in_squotes_join_tokens(t_minishell *minishell, t_token_list **list)
{
	t_token_list *cpy;

	cpy = (*list);
	while ((*list) != NULL && (*list)->next != NULL)
	{
		if ((*list)->e_operator == SINGLE_QUOTE && (*list)->next->e_operator == DOUBLE_QUOTE)
		{
			(*list) = (*list)->next;
			while ((*list)->next != NULL && (*list)->next->e_operator != SINGLE_QUOTE)
				join_tokens(minishell, list);
			(*list) = (*list)->next;
		}
		else
			(*list) = (*list)->next;
	}
	*list = cpy;
}
