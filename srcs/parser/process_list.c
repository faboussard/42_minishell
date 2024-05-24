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


void go_to_next_pipe(t_token_list **list)
{
	if (*list != NULL)
		*list = (*list)->next;
}

void iterate_until_next_pipe(t_token_list **list)
{
	while (*list != NULL && (*list)->e_operator != PIPE)
		*list = (*list)->next;
}


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
	new_process->next = NULL;
}

void create_process_list(t_minishell *m, t_process_list **pl)
{
	t_token_list	*temp;
	t_process_list	*new_pl;

	temp = m->list_tokens;
	while (m->list_tokens != NULL)
	{
		new_pl = ft_calloc(1, sizeof(t_process_list));
		if (new_pl == NULL)
			exit_msg_minishell(m, "malloc failed at create_process_list", ENOMEM);
		create_process_list_node(new_pl, m);
		add_process_to_list(pl, new_pl);
		iterate_until_next_pipe(&m->list_tokens);
		go_to_next_pipe(&m->list_tokens);
	}
	m->list_tokens = temp;
}