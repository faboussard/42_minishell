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
	}
	else
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
	t_process_list *new_process_list;
	t_token_list	*temp;

	count_total_commands(minishell);
	temp = minishell->list_tokens;
	while (minishell->list_tokens != NULL)
	{
		new_process_list = ft_calloc(1, sizeof(t_process_list));
		new_process_list = create_cmd_table(new_process_list, minishell);
		if (new_process_list == NULL)
			return;
//	get_in_files_token(minishell);
//	get_out_files_token(minishell->process_list);
		add_process_to_list(&minishell->process_list, new_process_list);
		while (minishell->list_tokens != NULL && minishell->list_tokens->e_operator != PIPE)
			minishell->list_tokens = minishell->list_tokens->next;
		if (minishell->list_tokens != NULL)
			minishell->list_tokens = minishell->list_tokens->next;
	}
	minishell->list_tokens = temp;
}
