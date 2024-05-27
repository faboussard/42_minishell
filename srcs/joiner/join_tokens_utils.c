/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/27 10:21:07 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include <stdlib.h>

void	join_tokens_safely(t_minishell *m, t_token_list **list,
		t_token_list *cpy)
{
	if (join_tokens(list) == MALLOC_FAILED)
	{
		*list = cpy;
		exit_msg(m, "Malloc failed at join_tokens", ENOMEM);
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
		exit_msg(NULL, "Malloc failed at join spaces", ENOMEM);
	(*list)->e_type = COMMAND;
	(*list)->e_operator = 0;
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
