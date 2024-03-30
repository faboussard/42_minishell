/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_list.c                                     :+:      :+:    :+:   */
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

t_process_list *ft_lstlast_process(t_process_list *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void add_process_to_list(t_process_list **process_list, t_process_list *new_process)
{
	t_process_list *last;

	if (*process_list != NULL)
	{
		last = ft_lstlast_process(*process_list);
		if (last != NULL)
			last->next = new_process;
	} else
		*process_list = new_process;
}

t_token *create_in_files_list(t_process_list *process_list)
{
	t_token *in_files_list;
	t_token *iterator;
	t_token *temp_token;

	temp_token = NULL;
	in_files_list = NULL;
	iterator = process_list->tokens_until_pipe;
	while (iterator!= NULL)
	{
		if (iterator->e_operator == INPUT_REDIRECT)
		{
			temp_token = iterator->next;
			iterator->next = NULL;
			add_token_to_list(&in_files_list, iterator->next);
			iterator = temp_token;
		}
		iterator = iterator->next;
	}
	return (in_files_list);
}

t_process_list *create_process_list(t_minishell *minishell, t_token *list_tokens)
{
	t_process_list *process_list;
	t_process_list *new_process;
	t_token *iterator_token;
	t_token *temp_token;
	t_process_list *iterator_process;

	iterator_token = list_tokens;
	process_list = NULL;
	while (iterator_token != NULL)
	{
		new_process = ft_calloc(1, sizeof(t_process_list));
		if (new_process == NULL)
			exit_msg(minishell, "Fatal : malloc failed", -1);
		while (iterator_token != NULL && iterator_token->e_operator != PIPE)
		{
			temp_token = iterator_token->next;
			iterator_token->next = NULL;
			add_token_to_list(&new_process->tokens_until_pipe, iterator_token);
			iterator_token = temp_token;
		}
		add_process_to_list(&process_list, new_process);
		if (iterator_token != NULL)
			iterator_token = iterator_token->next;
	}
	iterator_process = process_list;
	while (iterator_process != NULL)
	{
		iterator_process->cmd_table = create_cmd_table(minishell);
		if (iterator_process->cmd_table == NULL)
			return (NULL);
		iterator_process->in_files_list = create_in_files_list(process_list);
//		new_process->limiters = create_limiters_list(new_process);
		iterator_process = iterator_process->next;
	}
	process_list = iterator_process;
	return (process_list);
}
