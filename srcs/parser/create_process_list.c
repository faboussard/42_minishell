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

void create_in_files_list(t_token_list **in_files_list, t_minishell *minishell)
{
	t_token_list	*iterator;
	t_token_list 	*next;

	iterator = minishell->list_tokens;
	while (iterator != NULL && iterator->e_operator != PIPE)
	{
		next = iterator->next;
		if (iterator->e_type == IN_FILE || iterator->e_type == DELIMITER)
		{
			create_token(minishell, iterator->name, in_files_list);
//			(*in_files_list)->e_type = iterator->e_type;
//			(*in_files_list)->is_quoted_delimiter = iterator->is_quoted_delimiter;
		}
		iterator = next;
	}
}

void create_out_files_list(t_token_list **out_files_list, t_minishell *minishell)
{
	t_token_list	*iterator;
	t_token_list 	*next;

	iterator = minishell->list_tokens;
	while (iterator != NULL && iterator->e_operator != PIPE)
	{
		next = iterator->next;
		if (iterator->e_type == OUT_FILE || iterator->e_type == APPEND_FILE)
		{
			create_token(minishell, iterator->name, out_files_list);
//			(*out_files_list)->e_type = iterator->e_type;
//			(*out_files_list)->is_quoted_delimiter = iterator->is_quoted_delimiter;
		}
		iterator = next;
	}
}

void create_process_list_node(t_process_list **new_process_list, t_minishell *minishell)
{
	size_t nbr_cmds_letters_in_pipe;

	*new_process_list = ft_calloc(1, sizeof(t_process_list));
	if (*new_process_list == NULL)
		exit_msg(minishell, "malloc failed at create_process_list", ENOMEM);
	(*new_process_list)->in_files_list = NULL;
	(*new_process_list)->out_files_list = NULL;
	nbr_cmds_letters_in_pipe = count_letters_until_pipe(minishell->list_tokens);
	create_cmd_table_array(*new_process_list, nbr_cmds_letters_in_pipe, minishell);
	create_in_files_list(&((*new_process_list)->in_files_list), minishell);
	create_out_files_list(&((*new_process_list)->out_files_list), minishell);
}

