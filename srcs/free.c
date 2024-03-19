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
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../libft/inc/libft.h"
#include "minishell.h"

void	free_minishell(t_minishell *minishell)
{
	if (minishell->fd_in >= 0)
		close(minishell->fd_in);
	if (minishell->fd_out >= 0)
		close(minishell->fd_out);
	if (minishell->hm_env_variables)
		ft_hm_clear(&minishell->hm_env_variables, &free);
	if (minishell->list_tokens)
		ft_lstclear(&minishell->list_tokens , &free);
	if (minishell->token_array)
		ft_free_double_tab(minishell->token_array);
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
