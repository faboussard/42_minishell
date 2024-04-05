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

void create_in_out_files_token(t_process_list *new_process_list, t_minishell *minishell);

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
				return 0;
			}
            i++;
        }
        iterator = iterator->next;
	}
	array[i] = NULL;
	return (1);
}

//< coucou > fichierEX ls  < coucou -la < coucou
//met le resultat de "ls -la" dans fichier prout
//-c "echo ls > ls -l | ls -l "

void create_cmd_table_array(t_process_list *new_process_list, size_t size, t_minishell *minishell)
{
	new_process_list->cmd_table = ft_calloc(size, sizeof(char **));
	if (new_process_list->cmd_table == NULL)
		exit_msg(minishell, "Memory allocation failed for command table array", 2);
	if (fill_cmds_and_args_array(minishell->list_tokens, new_process_list->cmd_table) == 0)
		exit_msg(minishell, "Memory allocation failed at tokenization", 2);
}

void create_in_files_token(t_process_list *new_process_list, t_minishell *minishell)
{
	t_token_list *iterator;
	t_token_list *next;

	new_process_list->in_files_token = ft_calloc(1, sizeof(t_token_list));
	if (new_process_list->in_files_token == NULL)
		exit_msg(minishell, "Malloc failed at creating process outfiles list", 2);
	iterator = minishell->list_tokens;
	while (iterator != NULL && iterator->e_operator != PIPE)
	{
		next = iterator->next;
		if (iterator->e_type == IN_FILE || iterator->e_type == DELIMITER)
		{
			if (new_process_list->in_files_token->name)
				free(new_process_list->in_files_token->name);
			new_process_list->in_files_token->name = NULL;
			new_process_list->in_files_token->name = ft_strdup(iterator->name);
			if (new_process_list->in_files_token->name == NULL)
				exit_msg(minishell, "Memory allocation failed at tokenization", 2);
			new_process_list->in_files_token->e_type = iterator->e_type;
			new_process_list->in_files_token->next = NULL;
		}
		iterator = next;
	}
}

void create_out_files_token(t_process_list *new_process_list, t_minishell *minishell)
{
	t_token_list *iterator;
	t_token_list *next;

	new_process_list->out_files_token = ft_calloc(1, sizeof(t_token_list));
	if (new_process_list->out_files_token == NULL)
		exit_msg(minishell, "Malloc failed at creating process outfiles list", 2);
	iterator = minishell->list_tokens;
	while (iterator != NULL && iterator->e_operator != PIPE)
	{
		next = iterator->next;
		if (iterator->e_type == OUT_FILE || iterator->e_type == APPEND_FILE)
		{
			if (new_process_list->out_files_token->name)
				free(new_process_list->out_files_token->name);
			new_process_list->out_files_token->name = NULL;
			new_process_list->out_files_token->name = ft_strdup(iterator->name);
			if (new_process_list->out_files_token->name == NULL)
				exit_msg(minishell, "Memory allocation failed at tokenization", 2);
			new_process_list->out_files_token->e_type = iterator->e_type;
			new_process_list->out_files_token->next = NULL;
		}
		iterator = next;
	}
}

t_process_list *create_process_list_node(t_process_list *new_process_list, t_minishell *minishell)
{
	size_t nbr_cmds_letters_int_pipe;

	nbr_cmds_letters_int_pipe = count_letters_until_pipe(minishell->list_tokens);
	create_cmd_table_array(new_process_list, nbr_cmds_letters_int_pipe, minishell);
//	create_in_out_files_token(new_process_list, minishell);
	create_in_files_token(new_process_list, minishell);
	create_out_files_token(new_process_list, minishell);
	return (new_process_list);
}

void create_envp_table(t_minishell *minishell)
{
    t_envp_list *current;
	size_t i;

	i = 0;
	minishell->envp_table = ft_calloc(minishell->total_size_envp + 1, sizeof(char **));
	if (minishell->envp_table == NULL)
		return ;
    current = minishell->list_envp;
	while (current != NULL)
	{
		minishell->envp_table[i] = ft_strjoin(current->target, current->value);
		if (minishell->envp_table[i] == NULL)
        {
            ft_free_all_tab(minishell->envp_table);
            return;
        }
        current = current->next;
		i++;
	}
	minishell->envp_table[i] = NULL;
}


