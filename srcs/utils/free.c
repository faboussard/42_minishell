/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/16 18:21:49 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexer.h"
#include "minishell.h"
#include "utils.h"
#include <readline/history.h>
#include <stdlib.h>

// commentaire pour fanny de fanny : laisser les declaration de next,
//	invalid read sinon

void free_token(t_token_list *token)
{
	if (token != NULL)
	{
		free_safely_str(token->name);
		free(token);
		token = NULL;
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
			free(current->target);
		if (current->value != NULL)
			free(current->value);
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
		if (current->name != NULL)
			free(current->name);
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	ft_free_process_list(t_process_list **process_list)
{
	t_process_list	*current;
	t_process_list	*next;

	current = *process_list;
	while (current != NULL)
	{
		next = current->next;
		if (current->cmd_table)
			ft_free_all_tab(current->cmd_table);
		if (current->in_files_token)
			ft_lstclear_token(&current->in_files_token);f
		if (current->out_files_token)
			ft_lstclear_token(&current->out_files_token);
		free(current);
		current = next;
	}
	*process_list = NULL;
}

void	free_minishell(t_minishell *minishell)
{
	free_strs(minishell);
	close_fds(minishell->fd_in, minishell->fd_out);
	if (minishell->list_envp != NULL)
		ft_lstclear_envp(&minishell->list_envp);
	if (minishell->envp_table)
		ft_free_all_tab(minishell->envp_table);
	if (minishell->process_list)
		ft_free_process_list(&minishell->process_list);
	if (minishell->list_tokens)
		ft_lstclear_token(&minishell->list_tokens);
	check_and_delete_if_tmp_file_exists(HERE_DOC_TMP_FILE);
	rl_clear_history();
	close_all_fds();
}

void	ft_free_all_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_tab_from_i(void **tab, int j)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
