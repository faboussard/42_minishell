/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/06 14:38:22 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexer.h"
#include "minishell.h"
#include "utils.h"
#include <stdlib.h>

void	free_token(t_token_list *token)
{
	if (token != NULL)
	{
		free_safely_str(&(token->name));
		free(token);
	}
}

void	ft_lstclear_envp(t_envp_list **lst)
{
	t_envp_list	*current;
	t_envp_list	*next;

	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		if (current->target != NULL)
			free_safely_str(&(current->target));
		if (current->value != NULL)
			free_safely_str(&(current->value));
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	ft_lstclear_token(t_token_list **lst)
{
	t_token_list	*current;
	t_token_list	*next;

	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		free_safely_str(&current->name);
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	ft_free_process_list(t_process_list **process_list)
{
	t_process_list	*current;
	t_process_list	*next;

	if (*process_list == NULL)
		return ;
	current = *process_list;
	while (current != NULL)
	{
		next = current->next;
		if (current->cmd_table)
			ft_free_tab(&(current->cmd_table));
		if (current->in_files_list)
			ft_lstclear_token(&current->in_files_list);
		if (current->out_files_list)
			ft_lstclear_token(&current->out_files_list);
		close_fds(current->fd_in, current->fd_out);
		free(current);
		current = next;
	}
	process_list = NULL;
}

void	free_minishell(t_minishell *minishell)
{
	free_strs(minishell);
	if (minishell->list_envp != NULL)
		ft_lstclear_envp(&minishell->list_envp);
	if (minishell->pl)
		ft_free_process_list(&minishell->pl);
	if (minishell->list_tokens)
		ft_lstclear_token(&minishell->list_tokens);
	//check_and_delete_if_tmp_file_exists(HERE_DOC_TMP_FILE);
	rl_clear_history();
	close_all_fds(minishell, minishell->pl);
}
