/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:01:00 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/24 19:34:51 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"
#include "signals.h"

static void	deals_with_one_or_two_point(t_minishell *m, t_process_list *pl)
{
	if (ft_strncmp(pl->cmd_table[0], ".", 2) == 0)
		exit_command_not_found(m, ".", pl, 0);
	if (ft_strncmp(m->paths, "/no_path_set", 12) == 0
		&& ft_strncmp(pl->cmd_table[0], "..", 3) == 0)
	{
		ft_putstr_fd("minishell: ..: Is a directory\n", 2);
		free_safely_str(&(m->paths));
		chose_exit(m, 1, 126);
	}
}

static void	check_cmd_pathed_or_no_path(t_minishell *m, t_process_list *pl)
{
	if (ft_strncmp(pl->cmd_table[0], "..", 3) == 0)
		exit_command_not_found(m, pl->cmd_table[0], pl, 0);
	if ((ft_strchr(pl->cmd_table[0], '/'))
		&& (contains_only_charset(pl->cmd_table[0], "./")
			|| ft_strncmp(pl->cmd_table[0], "/", 1)
			|| ft_strncmp(pl->cmd_table[0], "./", 2)))
		exit_is_a_directory(m, pl->cmd_table[0], pl);
	if (ft_strncmp(m->paths, "/no_path_set", 12) == 0)
	{
		print_name(m, pl->cmd_table[0]);
		ft_free_pl_paths(m, pl);
		chose_exit(m, 1, 127);
	}
}

static void	deals_if_dir_or_file(t_minishell *m, t_process_list *pl)
{
	struct stat	path_stat;

	stat(pl->cmd_table[0], &path_stat);
	if (S_ISREG(path_stat.st_mode))
	{
		if (access(pl->cmd_table[0], F_OK) != 0 || access(pl->cmd_table[0],
				X_OK) != 0)
		{
			print_name(m, pl->cmd_table[0]);
			ft_free_pl_paths(m, pl);
			chose_exit(m, 1, 126);
		}
		chose_exit(m, 1, 0);
	}
	else if (S_ISDIR(path_stat.st_mode))
		exit_is_a_directory(m, pl->cmd_table[0], pl);
}

void	my_execve(t_minishell *m, t_process_list *pl)
{
	if (pl->cmd_table[0] && !exec_builtin(m, pl->cmd_table[0], pl->cmd_table)
		&& m->interrupted_here_doc == 0)
	{
		set_good_path_cmd(m, pl, pl->cmd_table[0]);
		close_pipes_and_fds(m, pl);
		execve(pl->good_path, pl->cmd_table, m->envp_table);
		deals_with_one_or_two_point(m, pl);
		check_cmd_pathed_or_no_path(m, pl);
		deals_if_dir_or_file(m, pl);
		if ((access(pl->good_path, F_OK) == 0 || ft_strncmp(pl->cmd_table[0],
					".", 1) || ft_strchr(pl->cmd_table[0], '/')))
		{
			print_name(m, pl->cmd_table[0]);
			ft_free_pl_paths(m, pl);
			chose_exit(m, 0, 0);
		}
		else
			exit_command_not_found(m, pl->cmd_table[0], pl, 0);
	}
	close_pipes_and_fds(m, pl);
	free_safely_str(&(m->paths));
	chose_exit(m, 1, m->status);
}
