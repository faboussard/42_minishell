/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:29:13 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/18 09:15:14 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab || !*tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	ft_init_process_list_and_minishell(t_minishell *m, t_process_list *pl)
{
	m->status = 0;
	m->tmp_in = 0;
	m->fd_in = -1;
	m->fd_out = -1;
	pl->dev_null = 0;
	pl->paths = NULL;
	pl->good_path = NULL;
	pl->tab_paths = NULL;
}

void	ft_free_pl_paths(t_minishell *minishell)
{
	if (minishell->paths != NULL)
		free(minishell->paths);
	if (minishell->process_list->good_path != NULL)
		free(minishell->process_list->good_path);
	if (minishell->process_list->tab_paths != NULL)
		ft_free_tab(minishell->process_list->tab_paths);
}
