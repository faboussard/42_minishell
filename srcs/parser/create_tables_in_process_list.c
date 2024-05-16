/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:43:37 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/02 09:44:15 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include "parser.h"

int fill_cmds_and_args_array(t_token_list *list_tokens, char **array)
{
	size_t i;
    t_token_list	*iterator;

	i = 0;
    iterator = list_tokens;
    while (iterator && iterator->e_operator != PIPE)
	{
        if (iterator->e_type == COMMAND || iterator->e_type == ARGUMENT)
        {
            array[i] = ft_strdup(iterator->name);
            if (array[i] == NULL)
			{
				ft_free_tab(&array);
				return (0);
			}
            i++;
        }
        iterator = iterator->next;
	}
	array[i] = NULL;
	return (1);
}

void create_cmd_table_array(t_process_list *new_process_list, size_t size, t_minishell *minishell)
{
	new_process_list->cmd_table = ft_calloc(size + 1, sizeof(char **));
	if (new_process_list->cmd_table == NULL)
		exit_msg(minishell, "Memory allocation failed for command table array", ENOMEM);
	if (fill_cmds_and_args_array(minishell->list_tokens, new_process_list->cmd_table) == 0)
		exit_msg(minishell, "Memory allocation failed at tokenization", ENOMEM);
}

