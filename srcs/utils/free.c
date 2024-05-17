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
	t_envp_list	*next;

	while ((*lst) != NULL)
	{
		next = (*lst)->next;
		if ((*lst)->target != NULL)
			free_safely_str(&((*lst)->target));
		if ((*lst)->value != NULL)
			free_safely_str(&((*lst)->value));
		free((*lst));
		(*lst) = next;
	}
	*lst = NULL;
}

void	ft_lstclear_token(t_token_list **lst)
{
	t_token_list	*next;

	while (*lst != NULL)
	{
		next = (*lst)->next;
		free_safely_str(&(*lst)->name);
		free((*lst));
		(*lst) = next;
	}
	*lst = NULL;
}

void	ft_free_process_list(t_process_list **process_list)
{
	t_process_list	*next;

	if (*process_list == NULL)
		return ;
	while (*process_list != NULL)
	{
		next = (*process_list)->next;
		if ((*process_list)->cmd_table)
			ft_free_tab(&((*process_list)->cmd_table));
		if ((*process_list)->in_files_list)
			ft_lstclear_token(&(*process_list)->in_files_list);
		if ((*process_list)->out_files_list)
			ft_lstclear_token(&(*process_list)->out_files_list);
		close_fds((*process_list)->fd_in, (*process_list)->fd_out);
		free((*process_list));
		(*process_list) = NULL;
		*process_list = next;
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
