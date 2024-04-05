/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:01:00 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/04 08:57:13 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	my_execve(t_minishell *m, t_process_list *pl)
{
	set_good_path_cmd(m, pl, pl->cmd_table[0]);
	dprintf(2, "my_execve : GOOD PATH\t===\t%s\n", pl->good_path);
	dprintf(2, "my_execve : CMD_TABLE[0]\t===\t%s\n", pl->cmd_table[0]);
	execve(pl->good_path, pl->cmd_table, m->envp_table);
	if (access(pl->good_path, F_OK) == 0)
		print_name_and_exit_perror(m, pl->cmd_table[0], 1);
	else
		exit_command_not_found(m, pl->cmd_table[0]);
}

static void	exec_one_cmd(t_minishell *m)
{
	//  enum e_token_operators	infile_token;
	//  enum e_token_operators	outfile_token;

	//  infile_token = m->process_list->in_files_list->e_operator;
	//  outfile_token = m->process_list->out_files_list->e_operator;
	//  if (infile_token == HERE_DOC) // SEGFAULT
	//  	here_doc(m, m->process_list->in_files_list->name);
	//  if (infile_token == INPUT_REDIRECT || infile_token == HERE_DOC)
	//  {
	//  	open_fd_infile(m, m->process_list->in_files_list);
	//  	m_safe_dup2(m, m->fd_in, STDIN_FILENO);
	//  }
	//  if (outfile_token == OUTPUT_REDIRECT || outfile_token == APPEND)
	//  {
	//  	open_fd_outfile(m, m->process_list->out_files_list->name);
	//  	m_safe_dup2(m, m->fd_out, STDOUT_FILENO);
	//  }
	m->pid2 = m_safe_fork(m);
	if (m->pid2 == 0)
		my_execve(m, m->process_list);
	else
		close_fds(m->fd_in, m->fd_out);
}

static void	wait_children_and_give_exit_status(t_minishell *m)
{
	int	status;

	while (waitpid(m->pid2, &status, 0) && errno != 10)
		;
	while (waitpid(-1, NULL, 0) && errno != 10)
		;
	m->status = WEXITSTATUS(status);
}

void	execute_cmds(t_minishell *minishell, size_t nb_cmds)
{
	if (nb_cmds < 1)
		return ;
	dprintf(2, "NOT YET !, %s\n", minishell->envp_table[0]);
	set_paths(minishell, minishell->envp_table);
	if (minishell->paths == NULL)
		return ;
	if (nb_cmds == 1)
		exec_one_cmd(minishell);
	else
		exec_several_cmds(minishell, minishell->process_list);
	wait_children_and_give_exit_status(minishell);
	//ft_free_node_process_list(minishell, minishell->process_list);
}
