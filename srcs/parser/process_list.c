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

t_process_list *create_process_list(t_minishell *minishell, t_token *list_tokens)
{
	t_process_list *process_list;
	t_process_list *new_process;
	t_token *current_token;

	current_token = list_tokens;
	process_list = NULL;
	while (current_token != NULL && current_token->e_operator != PIPE)
	{
		new_process = ft_calloc(1, sizeof(t_process_list));
		if (new_process == NULL)
			exit_msg(minishell, "Fatal : malloc failed", -1);
		new_process->cmd_table = create_cmd_table(minishell);
		if (new_process->cmd_table == NULL)
		{
			free(new_process);
			return (NULL);
		}
		add_process_to_list(&process_list, new_process);
		current_token = current_token->next;
	}
	return (process_list);
}
