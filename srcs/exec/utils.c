/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:29:13 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/24 19:36:56 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"

void	check_and_delete_if_tmp_file_exists(char *tmp_file)
{
	if (access(tmp_file, F_OK) == 0)
	{
		if (unlink(tmp_file) == -1)
			perror("");
	}
}

void	init_before_next_prompt(t_minishell *m)
{
	m->total_commands = 1;
	free_safely_str(&(m->user_input));
	ft_free_process_list(&(m->pl));
	ft_lstclear_token(&m->list_tokens);
}

void	ft_init_pl(t_minishell *m, t_process_list *pl)
{
	m->status = 0;
	m->tmp_in = 0;
	pl->fd_in = -1;
	pl->fd_out = -1;
	pl->dev_null = 0;
	pl->paths = NULL;
	pl->good_path = NULL;
	pl->tab_paths = NULL;
}

void	ft_free_pl_paths(t_minishell *minishell, t_process_list *pl)
{
	free_safely_str(&(minishell->paths));
	free_safely_str(&(pl->good_path));
	ft_free_tab(&(pl->tab_paths));
	ft_free_tab(&(pl->cmd_table));
	ft_free_tab(&(minishell->envp_table));
}
