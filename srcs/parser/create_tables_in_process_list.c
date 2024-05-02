/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:43:37 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/19 09:43:37 by faboussa         ###   ########.fr       */
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
				ft_free_all_tab(array);
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
		exit_msg(minishell, "Memory allocation failed for command table array", 2);
	if (fill_cmds_and_args_array(minishell->list_tokens, new_process_list->cmd_table) == 0)
		exit_msg(minishell, "Memory allocation failed at tokenization", 2);
}

void create_envp_table(t_minishell *minishell)
{
    t_envp_list *current;
	size_t i;

	i = 0;
	minishell->envp_table = ft_calloc(minishell->total_size_envp + 1, sizeof(char **));
	if (minishell->envp_table == NULL)
		exit_msg(minishell, "Malloc failed at create_envp_table", 2) ;
    current = minishell->list_envp;
	while (current != NULL)
	{
		if (current->value == NULL)
			minishell->envp_table[i] = ft_strdup(current->target);
		else
			minishell->envp_table[i] = ft_strjoin(current->target, current->value);
		if (minishell->envp_table[i] == NULL)
			exit_msg(minishell, "Malloc failed at create_envp_table", 2);
        current = current->next;
		i++;
	}
	minishell->envp_table[i] = NULL;
}


