/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/18 10:34:38 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include <stdlib.h>

void join_tokens_safely(t_minishell *m, t_token_list **list, t_token_list *cpy)
{
	if (join_tokens(list) == MALLOC_FAILED)
	{
		*list = cpy;
		exit_msg_minishell(m, "Malloc failed at join_tokens", ENOMEM);
	}
}

int	check_if_more_tokens(t_token_list **list, enum e_token_operators op)
{
	t_token_list	*cpy;

	cpy = (*list)->next;
	while (cpy != NULL)
	{
		if (cpy->e_operator == op)
			return (1);
		cpy = cpy->next;
	}
	return (0);
}

void	change_token_name(t_token_list **list, char *new_name)
{
	free_safely_str(&((*list)->name));
	(*list)->name = ft_strdup(new_name);
	if ((*list)->name == NULL)
		exit_msg_minishell(NULL, "Malloc failed at join between spaces",
				ENOMEM);
	(*list)->e_type = COMMAND;
	(*list)->e_operator = 0;
}

void	join_token_name(t_minishell *minishell, char *new_name,
		t_token_list **iterator, char **new_table)
{
	new_name = ft_strjoin((*new_table), (*iterator)->name);
	if (new_name == NULL)
		exit_msg_minishell(minishell,
				"Memory allocation failed at tokenization", ENOMEM);
	free_safely_str(&(*new_table));
	(*new_table) = new_name;
	(*iterator) = (*iterator)->next;
}

int	join_tokens(t_token_list **list)
{
	char			*joined_name;
	t_token_list	*t2;
	t_token_list	*t1;

	t1 = (*list);
	t2 = (*list)->next;
	if (t2 == NULL)
		return (0);
	joined_name = ft_strjoin(t1->name, t2->name);
	if (joined_name == NULL)
		return (MALLOC_FAILED);
	free_safely_str(&(t1->name));
	t1->name = ft_strdup(joined_name);
	free_safely_str(&joined_name);
	if (t1->name == NULL)
		return (MALLOC_FAILED);
	del_next_token(&t1);
	define_token_types(COMMAND, NO_BUILTIN, NO_OPERATOR, t1);
	return (0);
}