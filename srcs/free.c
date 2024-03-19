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


void free_token(void *content)
{
	t_token *token = (t_token *)content;
	if (token != NULL)
	{
		free(token->name);
		free(token);
	}
}

void	free_minishell(t_minishell *minishell)
{
	if (minishell->fd_in >= 0)
		close(minishell->fd_in);
	if (minishell->fd_out >= 0)
		close(minishell->fd_out);
	if (minishell->hm_env_variables)
		ft_hm_clear(&minishell->hm_env_variables, &free);
	if (minishell->list_tokens)
		ft_lstclear(&minishell->list_tokens , &free_token);
	if (minishell->cmd_table)
		ft_free_double_tab(minishell->cmd_table);
	if (minishell->in_redirect_table)
		ft_free_double_tab(minishell->in_redirect_table);
	if (minishell->out_redirect_table)
		ft_free_double_tab(minishell->out_redirect_table);
}

void	ft_free_double_tab(char **tab)
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
