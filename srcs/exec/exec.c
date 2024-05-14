/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:01:00 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/06 16:26:44 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"

bool	is_a_builtin(t_minishell *m, char *cmd, char **cmd_table)
{
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
	else if (cmd && ft_strncmp(cmd, "export", 5) == 0)
		m->status = ft_export(cmd_table, &m->list_envp, m);
	else
		return (0);
	set_or_get_last_status(m->status, 0);
	return (1);
}

void	my_execve(t_minishell *m, t_process_list *pl)
{
	if (pl->cmd_table[0] && !is_a_builtin(m, pl->cmd_table[0], pl->cmd_table))
	{
		set_good_path_cmd(m, pl, pl->cmd_table[0]);
		close_pipes(m->pipe_fd);
		close_fds(pl->fd_in, pl->fd_out);
		close_fds(m->tmp_in, 0);
		execve(pl->good_path, pl->cmd_table, m->envp_table);
		if (access(pl->good_path, F_OK) == 0)
		{
			ft_free_pl_paths(m, pl);
			print_name_and_exit_perror(m, pl->cmd_table[0], 1);
		}
		else
		{
			ft_free_pl_paths(m, pl);
			exit_command_not_found(m, pl->cmd_table[0]);
		}
	}
	free_safely_str(&(m->paths));
	free_minishell(m);
	exit(m->status);
}

static int	check_all_infiles(t_minishell *m, t_process_list *pl, struct s_token *infile)
{
	int	fd_in;

	if (infile == NULL)
		return (0);
	if (infile->next != NULL)
	{
		if (open_fd_infile(m, pl, &fd_in))
			return (1);
		close (fd_in);
	}
	else
		return (open_fd_infile(m, pl, &(pl->fd_in)));
	return (check_all_infiles(m, pl, infile->next));
}
static void	create_all_outfiles(t_minishell *m, struct s_token *outfile)
{
	int	fd_out;

	if (outfile == NULL)
		return ;
	if (outfile->e_type == OUT_FILE)
	{
		fd_out = open(outfile->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out < 0)
			print_name_and_give_status(m, outfile->name, 1);
		else
			close(fd_out);
	}
	create_all_outfiles(m, outfile->next);
}

static int	handle_infile_outfile(t_minishell *m, t_process_list *pl)
{
	enum e_token_type	infile_token;
	enum e_token_type	outfile_token;

	infile_token = pl->in_files_list->e_type;
	outfile_token = pl->out_files_list->e_type;
	if (infile_token == DELIMITER)
		here_doc(m, pl->in_files_list, &(pl->fd_in), pl);
	if (infile_token == IN_FILE || infile_token == DELIMITER)
	{
		if (open_fd_infile(m, pl, &(pl->fd_in)))
			return (1);
		m_safe_dup2(m, pl->fd_in, STDIN_FILENO);
		close(pl->fd_in);
	}
	if (outfile_token == OUT_FILE || outfile_token == APPEND_FILE)
	{
		if (check_all_infiles(m, pl, pl->in_files_list) == 1)
			return (1);
		open_fd_outfile(m, pl, pl->out_files_list->name);
		create_all_outfiles(m, pl->out_files_list->next);
//		if (open_fd_outfile(m, pl, pl->out_files_list->name))
		if (pl->fd_out < 0)
			return (1);
		m_safe_dup2(m, pl->fd_out, STDOUT_FILENO);
		close(pl->fd_out);
	}
	return (0);
}

static void	exec_one_cmd(t_minishell *m, t_process_list *pl)
{
	if (is_a_builtin(m, pl->cmd_table[0], pl->cmd_table))
		return ;
	m->pid2 = m_safe_fork(m);
	if (m->pid2 == 0)
	{
		if (handle_infile_outfile(m, pl) == 0)
			my_execve(m, pl);
		else
			exit(1);
	}
	else
	{
		waitpid(m->pid2, &(m->status), 0);
		m->status = WEXITSTATUS(m->status);
		close_fds(pl->fd_in, pl->fd_out);
	}
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
	m->status = set_or_get_last_status(m->status, 0);
	ft_free_pl_paths(m, m->pl);
}
