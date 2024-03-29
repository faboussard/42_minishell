/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:01:00 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/29 09:51:41 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	my_execve(char *path, char **av, char **env, t_minishell m)
{
	execve(m->path, m->cmd, m->envp_table);
	if (access(m->good_path, F_OK) == 0)
		print_name_and_exit_perror(m, m->cmd_args[0], 1);
	else
		exit_command_not_found(m, m->cmd_args[0]);
}

void	exec_one_cmd(t_minishell *m)
{
	t_pid only_pid;
	if (m->heredoc == 1)
		here_doc(t_minishell *m, char *limiter); // SAISIR LE LIMITER
	if (redirection in || m->here_doc == 1) // fichier en entree, style < fichier ou << si here_doc
	{
		open_fd_infile(INFILE_FILE);
		m_safe_dup2(fd_in, STDIN_FILENO);
	}
	if (redirection out) // fichier en sortie, style > fichier
	{
		open_fd_outfile(m->t_token->next, trunc_ou_append); // besoin definition plus claire de l'outfile final + savoir si c'est > ou >>
		m_safe_dup2(fd_out, STDOUT_FILENO);
	}
	only_pid = m_safe_fork(m);
	if (only_pid == 0)
		my_execve(m->path, m->cmd_table, m->envp_table);
	else
		close_fds(m->fd_in, m->fd_out);
}

void	exec_several_cmds(t_minishell *m)
{
	if (pipe(m->pipe_fd) == -1)
		exit_msg(m, "Error creating the pipe", -1);
	if (child == 1)
		first_child(p, cmd, env);
	else if (child == 3)
		last_child(p, cmd, env);
	else
		middle_child(p, cmd, env);
}

void	execute_cmds(t_minishell minishell, int nb_cmds)
{
	if (nb_cmds < 1)
		return ;
	if (nb_cmds == 1)
		exec_one_cmd(minishell);
	else
		exec_several_cmds(minishell);
}
