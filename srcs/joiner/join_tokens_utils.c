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

#include "lexer.h"
#include "utils.h"
#include <stdlib.h>


int check_if_more_tokens(t_token_list **list, enum e_token_operators op)
{
	t_token_list *cpy;

	cpy = (*list)->next;
	while (cpy != NULL)
	{
		if (cpy->e_operator == op)
			return (1);
		cpy = cpy->next;
	}
	return (0);
}


void change_token_name(t_minishell *minishell, t_token_list **list, char *new_name)
{
	char *new_list_name;

	new_list_name = ft_strdup(new_name);
	if (new_list_name == NULL)
		exit_msg(minishell, "Malloc failed at join between spaces", 2);
	free_safely_str(&((*list)->name));
	(*list)->name = new_list_name;
	(*list)->e_type = COMMAND;
	(*list)->e_operator = 0;
}
