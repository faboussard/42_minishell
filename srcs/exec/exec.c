/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:01:00 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/02 14:44:32 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"

/*
 * Check if the command is a builtin and execute it
 * IMPORTANT !!!
 * Problem: m->list_tokens is not a good parameter, should be pl
 * The list_tokens never changes, while pl is iterated over
 */
bool	is_a_builtin(t_minishell *m, char *cmd, char **cmd_table)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		m->status = ft_echo(cmd_table);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		m->status = ft_cd(m, cmd_table);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		m->status = ft_pwd(m);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		m->status = ft_exit(m, cmd_table);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		m->status = ft_env(m, cmd_table);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		m->status = ft_unset(m, cmd_table);
	else if (ft_strncmp(cmd, "export", 5) == 0)
		m->status = ft_export(cmd_table, &m->list_envp, m);
	else
		return (0);
	set_or_get_last_status(m->status, 0);
	return (1);
}

void	my_execve(t_minishell *m, t_process_list *pl)
{
	if (!is_a_builtin(m, pl->cmd_table[0], pl->cmd_table))
	{
		set_good_path_cmd(m, pl, pl->cmd_table[0]);
		execve(pl->good_path, pl->cmd_table, m->envp_table);
		if (access(pl->good_path, F_OK) == 0)
		{
			free_safely_str(&(m->paths));
			free_safely_str(&(pl->good_path));
			ft_free_tab(&(pl->cmd_table));
			ft_free_tab(&(m->envp_table));
			print_name_and_exit_perror(m, pl->cmd_table[0], 1);
		}
		else
		{
			free_safely_str(&(m->paths));
			free_safely_str(&(pl->good_path));
			ft_free_tab(&(pl->cmd_table));
			ft_free_tab(&(m->envp_table));
			exit_command_not_found(m, pl->cmd_table[0]);
		}
	}
	free_safely_str(&(m->paths));
	free_minishell(m);
	exit(m->status);
}

int	handle_infile_outfile(t_minishell *m, t_process_list *pl)
{
	enum e_token_type	infile_token;
	enum e_token_type	outfile_token;

	infile_token = pl->in_files_token->e_type;
	outfile_token = pl->out_files_token->e_type;
	if (infile_token == DELIMITER)
		here_doc(m, pl->in_files_token, &(pl->fd_in));
	if (infile_token == IN_FILE || infile_token == DELIMITER)
	{
		if (open_fd_infile(m, pl))
			return (1);
		m_safe_dup2(m, pl->fd_in, STDIN_FILENO);
		close(pl->fd_in);
	}
	if (outfile_token == OUT_FILE || outfile_token == APPEND_FILE)
	{
		if (open_fd_outfile(m, pl, pl->out_files_token->name))
			return (1);
		m_safe_dup2(m, pl->fd_out, STDOUT_FILENO);
		close(pl->fd_out);
	}
	return (0);
}

static void	exec_one_cmd(t_minishell *m, t_process_list *pl)
{
	m->pid2 = m_safe_fork(m);
	if (m->pid2 == 0)
	{
		if (handle_infile_outfile(m, pl))
			return ;
		my_execve(m, pl);
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
	ft_free_pl_paths(m);
}
