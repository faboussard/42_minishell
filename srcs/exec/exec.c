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
#include "signal.h"
#include "signals.h"

void	deals_with_single_or_double_point(t_minishell *m, t_process_list *pl)
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

void	deals_if_dir_or_file(t_minishell *m, t_process_list *pl)
{
	struct stat	path_stat;

	if (ft_strncmp(pl->cmd_table[0], "..", 3) == 0)
		exit_command_not_found(m, pl->cmd_table[0], pl, 0);
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
	if (pl->cmd_table[0] && !exec_builtin(m, pl->cmd_table[0], pl->cmd_table))
	{
		set_good_path_cmd(m, pl, pl->cmd_table[0]);
		close_pipes_and_fds(m, pl);
		execve(pl->good_path, pl->cmd_table, m->envp_table);
		deals_with_single_or_double_point(m, pl);
		deals_if_dir_or_file(m, pl);
		if ((ft_strchr(pl->cmd_table[0], '/'))
			&& (contains_only_charset(pl->cmd_table[0], "./")
				|| ft_strncmp(pl->cmd_table[0], "/", 1)
				|| ft_strncmp(pl->cmd_table[0], "./", 2)))
			exit_is_a_directory(m, pl->cmd_table[0], pl);
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

static void	exec_one_cmd(t_minishell *m, t_process_list *pl)
{
	if (check_all_infiles(m, pl) == 1 || create_all_outfiles(m, pl) == 1)
	{
		m->status = 1;
		close_fds(pl->fd_in, pl->fd_out);
		return ;
	}
	ignore_signals();
	if (is_one_arg_builtin(m) && exec_builtin(m, pl->cmd_table[0],
			pl->cmd_table))
		return ;
	m->pid2 = m_safe_fork(m);
	if (m->pid2 == 0)
	{
		signal_interrupt();
		handle_infile_outfile(m, pl);
		my_execve(m, pl);
	}
	else
	{
		waitpid(m->pid2, &(m->status), 0);
		close_fds(pl->fd_in, pl->fd_out);
	}
	manage_interrupted_signal(m);
}

void	execute_cmds(t_minishell *m, size_t nb_cmds)
{
	if (nb_cmds < 1)
		return ;
	set_paths(m, m->envp_table);
	if (m->paths == NULL)
		return ;
	if (nb_cmds == 1)
		exec_one_cmd(m, m->pl);
	else
		exec_several_cmds(m, m->pl);
	ft_free_pl_paths(m, m->pl);
	check_and_delete_if_tmp_file_exists(HERE_DOC_TMP_FILE);
	m->status = set_or_get_last_status(m->status, 0);
}
