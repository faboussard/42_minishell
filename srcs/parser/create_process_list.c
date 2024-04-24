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

void create_in_files_token(t_process_list *new_process_list, t_minishell *minishell)
{
	t_token_list	*iterator;
	t_token_list 	*next;

	new_process_list->in_files_token = ft_calloc(1, sizeof(t_token_list));
	if (new_process_list->in_files_token == NULL)
		exit_msg(minishell, "Malloc failed at create_in_files_token", 2);
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
				exit_msg(minishell, "Memory allocation failed at create_in_files_token", 2);
			new_process_list->in_files_token->e_type = iterator->e_type;
			new_process_list->in_files_token->next = NULL;
		}
		iterator = next;
	}
}

void create_out_files_token(t_process_list *new_process_list, t_minishell *minishell)
{
	t_token_list	*iterator;
	t_token_list	*next;

	new_process_list->out_files_token = ft_calloc(1, sizeof(t_token_list));
	if (new_process_list->out_files_token == NULL)
		exit_msg(minishell, "Malloc failed at create_out_files_token", 2);
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
				exit_msg(minishell, "Memory allocation failed at create_out_files_token", 2);
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
	create_in_files_token(new_process_list, minishell);
	create_out_files_token(new_process_list, minishell);
	return (new_process_list);
}

