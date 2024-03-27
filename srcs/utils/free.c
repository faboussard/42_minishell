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


void free_token(t_token *token)
{
	if (token != NULL)
	{
		free(token->name);
		free(token);
	}
}

void free_t_envp_content(t_envp_content *envp)
{
	if (envp != NULL)
	{
		if (envp->target)
			free(envp->target);
		if (envp->value)
			free(envp->value);
		free(envp);
	}
}

void	free_minishell(t_minishell *minishell)
{
	if (minishell->fd_in >= 0)
		close(minishell->fd_in);
	if (minishell->fd_out >= 0)
		close(minishell->fd_out);
	if (minishell->user_input)
		free(minishell->user_input);
	if (minishell->list_tokens)
		ft_lstclear(&minishell->list_tokens, (void *) free_token);
	if (minishell->list_envp != NULL)
		ft_lstclear(&minishell->list_envp, (void *) free_t_envp_content);
	if (minishell->envp_table)
		ft_free_all_tab(minishell->envp_table);
	if (minishell->cmd_table)
		ft_free_all_tab(minishell->cmd_table);
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


