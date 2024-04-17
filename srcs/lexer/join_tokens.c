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
	del_next_token(&t1);
	define_token_types(COMMAND, NO_BUILTIN, NO_OPERATOR, t1);
}

void join_between_quotes(t_minishell *minishell, t_token_list **list, enum e_token_operators op)
{
	int count;

	count = 1;
	if (*list == NULL || (*list)->next == NULL || (*list)->next->next == NULL)
		return;
	(*list) = (*list)->next;
	while ((*list) && (*list)->next)
	{
		if ((*list)->e_operator == op)
			count++;
		if (count == 2 && (*list)->next->e_operator == op && (*list)->next->next && (*list)->next->next->e_operator != IS_SPACE)
		{
			del_next_token(list);
			join_tokens(minishell, list);
		}
		else
			break;
	}
//	if (count == 2)
//	{
//		while ((*list) && (*list)->next && (*list)->next->e_operator != IS_SPACE)
//		{
//			if ((*list)->e_operator == op)
//				(*list) = (*list)->next;
//			else if ((*list)->next->e_operator == op)
//			{
//				(*list) = (*list)->next;
//				(*list) = (*list)->next;
//			}
//			else
//				join_tokens(minishell, list);
//		}
//	}
}

//void join_dollar_and_after_double_quote(t_token_list **list)
//{
//	t_token_list *current = *list;
//
//	while (current != NULL && current->next != NULL)
//	{
//		if (current->e_operator == DOLLAR && current->next->e_operator == DOUBLE_QUOTE)
//		{
//			t_token_list *to_remove = current;
//			current = current->next->next;
//			remove_node(list, to_remove);
//			continue;
//		}
//		current = current->next;
//	}
//}


//void delete_dollar_before_join(t_token_list **list)
//{
//	t_token_list *cpy;
//
//	cpy = *list;
//	while (*list != NULL && (*list)->next != NULL)
//	{
//		if ((*list)->e_operator == DOUBLE_QUOTE && (*list)->next->e_operator == DOLLAR)
//			del_next_token(list);
////		if ((*list)->e_operator == DOLLAR && (*list)->next->e_operator == DOUBLE_QUOTE)
////			remove_node(list, (*list));
//		(*list) = (*list)->next;
//	}
//	*list = cpy;
//}

int check_if_more_tokens(t_token_list **list, enum e_token_operators op)
{
	t_token_list *cpy;

	cpy = (*list)->next;
	while (cpy != NULL)
	{
		if (cpy->e_operator == op)
			return 1;
		cpy = cpy->next;
	}
	return 0;
}


void join_quotes(t_minishell *minishell, t_token_list **list)
{
	t_token_list *cpy;

	cpy = *list;
	while (*list != NULL && (*list)->next != NULL)
	{
		if (((*list)->e_operator == DOUBLE_QUOTE && (*list)->next->e_operator == DOUBLE_QUOTE)
		|| ((*list)->e_operator == SINGLE_QUOTE && (*list)->next->e_operator == SINGLE_QUOTE))
		{
			(*list) = (*list)->next;
			(*list) = (*list)->next;
		}
		else if ((*list)->e_operator == DOUBLE_QUOTE && check_if_more_tokens(list, DOUBLE_QUOTE))
		{
			join_between_quotes(minishell, list, DOUBLE_QUOTE);
			if ((*list) == NULL)
				break;
		}
		else if ((*list)->e_operator == SINGLE_QUOTE && check_if_more_tokens(list, SINGLE_QUOTE))
		{
			join_between_quotes(minishell, list, SINGLE_QUOTE);
			if ((*list) == NULL)
				break;
		}
		else
			(*list) = (*list)->next;
	}
	*list = cpy;
	remove_sep_tokens(minishell);
	ft_list_remove_if(&minishell->list_tokens, (void *) DOLLAR, cmp);
}

//void join_dollar_and_single_quote(t_minishell *minishell, t_token_list **list)
//{
//	t_token_list *cpy;
//
//	cpy = *list;
//	while (*list != NULL && (*list)->next != NULL)
//	{
//		if ((*list)->e_operator == SINGLE_QUOTE && (*list)->next->e_operator == DOLLAR)
//			join_between_quotes(minishell, list, SINGLE_QUOTE);
//		(*list) = (*list)->next;
//	}
//	*list = cpy;
//}

void join_spaces(t_minishell *minishell, t_token_list **list)
{
	t_token_list *cpy;

	cpy = *list;
	while (*list != NULL && (*list)->next != NULL)
	{
		if ((*list)->e_operator == IS_SPACE)
			*list = (*list)->next;
		while ((*list) != NULL && (*list)->next != NULL && (*list)->next->e_operator != IS_SPACE)
				join_tokens(minishell, list);
	}
	*list = cpy;
	ft_list_remove_if(&minishell->list_tokens, (void *) IS_SPACE, cmp);
}

