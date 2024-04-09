/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:01:00 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/09 14:45:15 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	my_execve(t_minishell *m, t_process_list *pl)
{
	set_good_path_cmd(m, pl, pl->cmd_table[0]);
	execve(pl->good_path, pl->cmd_table, m->envp_table);
	if (access(pl->good_path, F_OK) == 0)
		print_name_and_exit_perror(m, pl->cmd_table[0], 1);
	else
		exit_command_not_found(m, pl->cmd_table[0]);
}

static void	check_stdin_stdout(enum e_token_type in, enum e_token_type out)
{
	if (in == IN_FILE || in == DELIMITER)
		close(STDIN_FILENO);
	if (out == OUT_FILE || out == APPEND_FILE)
		close(STDOUT_FILENO);
}

void	handle_infile_outfile(t_minishell *m, t_process_list *pl)
{
	enum e_token_type	infile_token;
	enum e_token_type	outfile_token;

	infile_token = pl->in_files_token->e_type;
	outfile_token = pl->out_files_token->e_type;
	if (infile_token == DELIMITER)
		here_doc(m, pl->in_files_token->name);
	if (infile_token == IN_FILE || infile_token == DELIMITER)
	{
		open_fd_infile(m, pl->in_files_token);
		m_safe_dup2(m, m->fd_in, STDIN_FILENO);
		close(m->fd_in);
	}
	if (outfile_token == OUT_FILE || outfile_token == APPEND_FILE)
	{
		open_fd_outfile(m, pl, pl->out_files_token->name);
		m_safe_dup2(m, m->fd_out, STDOUT_FILENO);
		close(m->fd_out);
	}
}

static void	exec_one_cmd(t_minishell *m, t_process_list *pl)
{
	enum e_token_type	infile_token;
	enum e_token_type	outfile_token;

	infile_token = pl->in_files_token->e_type;
	outfile_token = pl->out_files_token->e_type;
	handle_infile_outfile(m, pl);
	m->pid2 = m_safe_fork(m);
	if (m->pid2 == 0)
		my_execve(m, pl);
	else
	{
		waitpid(m->pid2, &(m->status), 0);
		m->status = WEXITSTATUS(m->status);
		check_stdin_stdout(infile_token, outfile_token);
		close_fds(m->fd_in, m->fd_out);
	}
}

void	execute_cmds(t_minishell *minishell, size_t nb_cmds)
{
	int	stdin_orig;
	int	stdout_orig;

	stdin_orig = dup(STDIN_FILENO);
	stdout_orig = dup(STDOUT_FILENO);
	if (stdin_orig == -1 || stdout_orig == -1)
	{
		ft_putendl_fd("minishell : dup error", 2);
		return ;
	}
	if (nb_cmds < 1)
		return ;
	set_paths(minishell, minishell->envp_table);
	if (minishell->paths == NULL)
		return ;
	if (nb_cmds == 1)
		exec_one_cmd(minishell, minishell->process_list);
	else
		exec_several_cmds(minishell, minishell->process_list);
	ft_free_pl_paths(minishell);
	m_safe_dup2(minishell, stdin_orig, STDIN_FILENO);
	close(stdin_orig);
	m_safe_dup2(minishell, stdout_orig, STDOUT_FILENO);
	close(stdout_orig);
}
