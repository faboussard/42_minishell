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

void del_next_token(t_token_list **token)
{
	t_token_list *t2;
	t_token_list *t1;

	t1 = (*token);
	t2 = (*token)->next;
	t1->next = t2->next;
	free_token(t2);
	t1 = t1->next;
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
	define_token_types(COMMAND, NO_BUILTIN, NO_OPERATOR, t1);
	del_next_token(&t1);
}

void in_op_for_join(t_minishell *minishell, t_token_list **list, enum e_token_operators op)
{
	if (*list == NULL)
		return;
	*list = (*list)->next;
	while ((*list) != NULL && (*list)->next != NULL && (*list)->next->e_operator != op)
		join_tokens(minishell, list);
}

void join_quotes(t_minishell *minishell, t_token_list **list)
{
	t_token_list *cpy;

	cpy = *list;
	while (*list != NULL && (*list)->next != NULL)
	{
		if ((*list)->e_operator == DOUBLE_QUOTE)
		{
			in_op_for_join(minishell, list, DOUBLE_QUOTE);
		}
		if ((*list)->e_operator == SINGLE_QUOTE)
		{
			in_op_for_join(minishell, list, SINGLE_QUOTE);
		}
		(*list) = (*list)->next;
	}
	*list = cpy;
	ft_list_remove_if(&minishell->list_tokens, (void *) SINGLE_QUOTE, cmp);
	ft_list_remove_if(&minishell->list_tokens, (void *) DOUBLE_QUOTE, cmp);
}

void join_spaces(t_minishell *minishell, t_token_list **list)
{
	t_token_list *cpy;

	cpy = *list;
	while (*list != NULL && (*list)->next != NULL)
	{
		if ((*list)->next->e_operator == IS_SPACE || ((*list)->e_operator == IS_SPACE && *list == cpy))
		{
			in_op_for_join(minishell, list, IS_SPACE);
			if (*list == NULL)
				break;
		}
		(*list) = (*list)->next;
	}
	*list = cpy;
	ft_list_remove_if(&minishell->list_tokens, (void *) IS_SPACE, cmp);
}
