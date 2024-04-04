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

void get_in_files_token(t_minishell *minishell)
{
	t_token_list *iterator;

	iterator = minishell->list_tokens;
	while (iterator!= NULL)
	{
		if (iterator->e_operator == INPUT_REDIRECT || iterator->e_operator == HERE_DOC)
			minishell->process_list->in_files_list = iterator;
		iterator = iterator->next;
	}
	minishell->process_list->in_files_list->e_operator = NO_OPERATOR;
}

void create_process_list(t_minishell *minishell)
{
	minishell->process_list = ft_calloc(1, sizeof(t_process_list));
	create_cmd_table(minishell);
	if (minishell->process_list->cmd_table == NULL)
		return ;
//	get_in_files_token(minishell);
//	get_out_files_token(minishell->process_list);
//	add_process_to_list(&minishell->process_list, minishell->process_list);
}
