/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl.c                                     :+:      :+:    :+:   */
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

//
//void create_in_out_files_token(t_process_list *new_process_list, t_minishell *minishell)
//{
//	t_token_list *current;
//
//	current = minishell->list_tokens;
//	new_process_list->in_out_files_tokens = ft_calloc(1, sizeof(t_token_list));
//	new_process_list->in_out_files_tokens = current;
//	ft_list_remove_if(new_process_list->in_out_files_tokens);
//}
//
//void ft_list_remove_if(t_token_list *begin_list)
//{
//	t_token_list	*cur;
//
//	if (begin_list == NULL)
//		return;
//	cur = begin_list;
//	if (begin_list->e_type != APPEND_FILE && begin_list->e_type != IN_FILE && begin_list->e_type
//	!= OUT_FILE && begin_list->e_type != DELIMITER)
//	{
//		begin_list = cur->next;
//		free(cur);
//		ft_list_remove_if(begin_list);
//	}
//	else
//	{
//		cur = begin_list;
//		ft_list_remove_if(cur->next);
//	}
//}


void create_process_list(t_minishell *minishell)
{
	t_process_list	*new_process_list;
	t_token_list	*temp;

	minishell->total_commands += count_token_by_operator(minishell, PIPE);
	temp = minishell->list_tokens;
	while (minishell->list_tokens != NULL)
	{
		new_process_list = ft_calloc(1, sizeof(t_process_list));
		if (new_process_list == NULL)
			exit_msg(minishell, "malloc failed at create_process_list", 2);
		new_process_list = create_process_list_node(new_process_list, minishell);
		if (new_process_list == NULL)
			return;
		add_process_to_list(&minishell->pl, new_process_list);
		while (minishell->list_tokens != NULL && minishell->list_tokens->e_operator != PIPE)
			minishell->list_tokens = minishell->list_tokens->next;
		if (minishell->list_tokens != NULL)
			minishell->list_tokens = minishell->list_tokens->next;
	}
	minishell->list_tokens = temp;
}
