/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:29:13 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/04 08:53:40 by mbernard         ###   ########.fr       */
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
	m->tmp_in = -1;
	m->fd_in = -1;
	m->fd_out = -1;
	//pl->here_doc = 0;
	pl->dev_null = 0;
	pl->paths = NULL;
	pl->good_path = NULL;
	pl->tab_paths = NULL;
}

void	ft_free_node_process_list(t_minishell *m, t_process_list *pl)
{
	if (pl->paths)
		free(pl->paths);
	if (pl->good_path)
		free(pl->good_path);
	if (pl->tab_paths)
		ft_free_tab(pl->tab_paths);
	if (pl->cmd_table)
		ft_free_tab(pl->cmd_table);
	check_and_delete_if_tmp_file_exists("/tmp/.tmp_heredoc");
	if (m->fd_in >= 0)
		close(m->fd_in);
	if (m->fd_out >= 0)
		close(m->fd_out);
	close(STDOUT_FILENO);
}
