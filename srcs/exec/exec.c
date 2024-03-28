/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:01:00 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/28 13:35:08 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//------------------SERA DANS UN FICHIER fd_management.c ENSUITE --//
void	open_fd_infile(t_minishell *m, char *in)
{
	if (m->here_doc == 0)
		m->fd_in = open(in, O_RDONLY);
	else if (m->here_doc == 1)
		m->fd_in = open("/tmp/.tmp_heredoc", O_RDONLY);
	if (m->fd_in < 0)
	{
		print_name(p, in);
		m->status = 1;
		m->dev_null = 1;
		m->fd_in = open("/dev/null", O_RDONLY);
		if (m->fd_in < 0)
			exit_msg_pipex(NULL, "No /dev/null/ found", -1);
	}
}

void	open_fd_outfile(t_minishell *m, char *out, bool trunk_or_append)
{
	if (trunk_or_append == 0)
		m->fd_out = open(out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (trunk_or_append == 1)
		m->fd_out = open(out, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (m->fd_out < 0)
		print_name_and_exit_perror(p, out, 1);
}
//---------------------------fin fd_management.c-------------------//
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
	t_pid	only_pid;

	if (redirection in) // fichier en entree, style < fichier
	{
		open_fd_infile(INFILE_FILE);
		dup2(fd_in, STDIN_FILENO);
	}
	if (redirection out) // fichier en sortie, style > fichier
	{
		open_fd_outfile(m->t_token->next, trunc_ou_append);
    dup2(fd_out, STDOUT_FILENO);
	}
	only_pid = m_safe_fork(m);
	if (only_pid == 0)
		my_execve(m->path, m->cmd_table, m->envp_table);
	else
	{
		if (redirection in)
			ok;
		if (redirection out)
		ifredir
		    dup2(fd_in, STDIN_FILENO);
    dup2(fd_out, STDOUT_FILENO);

    execve("/bin/cat", argv, envp);
    perror("execve");

    close(fd_in);
    close(fd_out);
	}
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

void	execute(t_minishell minishell, int nb_cmds)
{
	if (nb_cmds < 1)
		return ;
	if (nb_cmds == 1)
		exec_one_cmd(minishell);
	else
		exec_several_cmds(minishell);
}
