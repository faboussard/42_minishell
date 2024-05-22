/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:01:00 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/16 21:17:12 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"
#include "signal.h"
#include "signals.h"

static int	create_all_outfiles(t_minishell *m, t_process_list *pl);
static int	check_all_infiles(t_minishell *m, t_process_list *pl);

bool	is_one_arg_builtin(t_minishell *m)
{
	if (m->total_commands == 1)
	{
		if (m->list_tokens->e_builtin == EXIT)
			return (1);
		if (m->list_tokens->e_builtin == UNSET)
			return (1);
		if (m->list_tokens->e_builtin == CD)
			return (1);
		if (m->list_tokens->e_builtin == EXPORT)
			return (1);
	}
	return (0);
}

bool	is_a_builtin(t_minishell *m, char *cmd, char **cmd_table)
{
	if (!cmd || !cmd_table)
		return (0);
	if (cmd && ft_strncmp(cmd, "echo", 5) == 0)
		m->status = ft_echo(cmd_table);
	else if (cmd && ft_strncmp(cmd, "cd", 3) == 0)
		m->status = ft_cd(m, cmd_table);
	else if (cmd && ft_strncmp(cmd, "pwd", 4) == 0)
		m->status = ft_pwd(m);
	else if (cmd && ft_strncmp(cmd, "exit", 5) == 0)
		m->status = ft_exit(m, cmd_table);
	else if (cmd && ft_strncmp(cmd, "env", 4) == 0)
		m->status = ft_env(m, cmd_table);
	else if (cmd && ft_strncmp(cmd, "unset", 6) == 0)
		m->status = ft_unset(m, cmd_table);
	else if (cmd && ft_strncmp(cmd, "export", 7) == 0)
		m->status = ft_export(cmd_table, &m->list_envp, m);
	else
		return (0);
	set_or_get_last_status(m->status, 0);
	return (1);
}

void close_pipes_and_fds(t_minishell *m, t_process_list *pl)
{
	close_pipes(m->pipe_fd);
	close_fds(pl->fd_in, pl->fd_out);
	close_fds(m->tmp_in, 0);
}

void	chose_exit(t_minishell *m, bool good_code, int exit_code)
{
	free_minishell(m);
	if (good_code)
		exit(exit_code);
	if (errno == 13)
		exit(126);
	if (errno == 2)
		exit(127);
	exit(1);
}

void deals_with_single_point(t_minishell *m, t_process_list *pl)
{
	if (ft_strncmp(pl->cmd_table[0], ".", 2) == 0
		&& !pl->cmd_table[1])
	{
		ft_putstr_fd("minishell: .: filename argument required\n"
					 ".: usage: . filename [arguments]\n", 2);
		free_safely_str(&(m->paths));
		free_minishell(m);
		exit(2);
	}
}

void	deals_if_dir_or_file(t_minishell *m, t_process_list *pl)
{
	struct stat path_stat;

	stat(pl->cmd_table[0], &path_stat);
	if (S_ISREG(path_stat.st_mode))
	{
		if (access(pl->cmd_table[0], X_OK) != 0)
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
	if (pl->cmd_table[0] && !is_a_builtin(m, pl->cmd_table[0], pl->cmd_table))
	{
		set_good_path_cmd(m, pl, pl->cmd_table[0]);
		close_pipes_and_fds(m, pl);
		execve(pl->good_path, pl->cmd_table, m->envp_table);
		deals_with_single_point(m, pl);
		deals_if_dir_or_file(m, pl);
		if (access(pl->good_path, F_OK) == 0
			&& ft_strncmp(pl->cmd_table[0], "..", 3))
		{
			print_name(m, pl->cmd_table[0]);
			ft_free_pl_paths(m, pl);
			chose_exit(m, 0, 0);
		}
		else
			exit_command_not_found(m, pl->cmd_table[0], pl);
	}
	free_safely_str(&(m->paths));
	chose_exit(m, 1, m->status);
}

static int	check_all_infiles(t_minishell *m, t_process_list *pl)
{
	t_process_list	*tmp;
	int				fd_in;

	if (pl->in_files_list == NULL)
		return (0);
	tmp = pl;
	fd_in = 0;
	while (tmp->in_files_list && tmp->in_files_list->next)
	{
		if (tmp->in_files_list->e_type == DELIMITER)
			here_doc(m, tmp->in_files_list, &fd_in, tmp);
		if (open_fd_infile(m, tmp, tmp->in_files_list->name, &fd_in) == 0)
			close(fd_in);
		else
			return (1);
		tmp->in_files_list = tmp->in_files_list->next;
	}
	if (tmp->in_files_list)
	{
		if (tmp->in_files_list->e_type == DELIMITER)
			here_doc(m, tmp->in_files_list, &(pl->fd_in), tmp);
		if (open_fd_infile(m, tmp, tmp->in_files_list->name, &(pl->fd_in)))
			return (1);
	}
	return (0);
}

static int	create_all_outfiles(t_minishell *m, t_process_list *pl)
{
	t_process_list	*tmp;
	int				fd_out;

	if (pl->out_files_list == NULL)
		return (0);
	tmp = pl;
	while (tmp->out_files_list && tmp->out_files_list->next)
	{
		fd_out = open(tmp->out_files_list->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			print_name_and_give_status(m, tmp->out_files_list->name, 1);
			return (1);
		}
		close(fd_out);
		tmp->out_files_list = tmp->out_files_list->next;
	}
	if (tmp->out_files_list)
	{
		if (open_fd_outfile(m, tmp, tmp->out_files_list->name) == 1)
			return (1);
	}
	return (0);
}

static int	handle_infile_outfile(t_minishell *m, t_process_list *pl)
{
	if (pl->in_files_list != NULL)
	{
		m_safe_dup2(m, pl->fd_in, STDIN_FILENO);
		close(pl->fd_in);
	}
	if (pl->out_files_list != NULL)
	{
		m_safe_dup2(m, pl->fd_out, STDOUT_FILENO);
		close(pl->fd_out);
	}
	return (0);
}

void	manage_interrupted_signal(t_minishell *m)
{
	if (WIFSIGNALED(m->status))
		m->status = set_or_get_last_status(128 + WTERMSIG(m->status), 0);
	else if (WIFEXITED(m->status))
		m->status = WEXITSTATUS(m->status);
	else
		m->status = set_or_get_last_status(m->status, 0);
}

static void	exec_one_cmd(t_minishell *m, t_process_list *pl)
{
	if (check_all_infiles(m, pl) == 1 || create_all_outfiles(m, pl) == 1)
	{
		m->status = 1;
		return ;
	}
	if (is_one_arg_builtin(m) && is_a_builtin(m, pl->cmd_table[0], pl->cmd_table))
		return ;
	m->pid2 = m_safe_fork(m);
	if (m->pid2 == 0)
	{
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
	signal_interrupt();
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
//	set_or_get_last_status(WIFEXITED(m->status), 0);
	//m->status = WEXITSTATUS(m->status);
	check_and_delete_if_tmp_file_exists(HERE_DOC_TMP_FILE);
	m->status = set_or_get_last_status(m->status, 0);
}
