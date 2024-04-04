/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                              :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdlib.h>
#include "minishell.h"
# include <readline/history.h>

void ft_lstclear_envp(t_envp_list **lst)
{
    t_envp_list *current;
	t_envp_list *next;

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

void ft_lstclear_token(t_token_list **lst)
{
    t_token_list *current;
    t_token_list *next;

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

void ft_free_process_list(t_process_list **process_list)
{
	t_process_list *current;
	t_process_list *next;

	current = *process_list;
	while (current != NULL)
	{
		next = current->next;
		if (current->cmd_table)
			ft_free_all_tab(current->cmd_table);
		if (current->tokens_until_pipe)
			ft_lstclear_token(&current->tokens_until_pipe);
		if (current->in_files_list)
			ft_lstclear_token(&current->in_files_list);
		if (current->out_files_list)
			ft_lstclear_token(&current->out_files_list);
		free(current);
		current = next;
	}
	*process_list = NULL;
}

void	free_minishell(t_minishell *minishell)
{
	if (minishell->fd_in >= 0)
		close(minishell->fd_in);
	if (minishell->fd_out >= 0)
		close(minishell->fd_out);
	if (minishell->user_input)
		free(minishell->user_input);
	if (minishell->list_envp != NULL)
        ft_lstclear_envp(&minishell->list_envp);
	if (minishell->envp_table)
		ft_free_all_tab(minishell->envp_table);
	if (minishell->process_list)
		ft_free_process_list(&minishell->process_list);
//	if (minishell->list_tokens)
//		ft_lstclear_token(&minishell->list_tokens);
	if (minishell->history_count != 0)
		rl_clear_history();
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


