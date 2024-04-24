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
			return 1;
		cpy = cpy->next;
	}
	return 0;
}


void change_iterator_name_to_empty_string(t_minishell *minishell, t_token_list **list)
{
	char *empty_string;
	empty_string = ft_strdup("\0");
	if (empty_string == NULL)
		exit_msg(minishell, "Malloc failed at join between spaces", 2);
	free((*list)->name);
	(*list)->name = empty_string;
	(*list)->e_type = COMMAND;
	(*list)->e_operator = 0;
}
