/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:01:00 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/05 11:13:01 by mbernard         ###   ########.fr       */
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

static void check_stdin_stdout(enum e_token_type	in, enum e_token_type	out)
{
    if (in == IN_FILE || in == DELIMITER)
    {
        close(STDIN_FILENO);
/* Even if closed, it seems to reopen itself right away*/
    }
    if (out == OUT_FILE || out == APPEND_FILE)
    {
        close(STDOUT_FILENO);
        if (open("/dev/tty", O_WRONLY) == -1)
            ft_putendl_fd("Can't open standard output", 2);
    }
}

static void	exec_one_cmd(t_minishell *m,  t_process_list *pl)
{
	  enum e_token_type	infile_token;
	  enum e_token_type	outfile_token;

	  infile_token = pl->in_files_token->e_type;
	  outfile_token = pl->out_files_token->e_type;
		dprintf(2, "Infile_token\t===\t%d\t===\t%s\n", infile_token, pl->in_files_token->name);
		dprintf(2, "Outfile_token\t===\t%d\t===\t%s\n", outfile_token, pl->out_files_token->name);
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
	  	open_fd_outfile(m, pl->out_files_token->name);
	  	m_safe_dup2(m, m->fd_out, STDOUT_FILENO);
		close(m->fd_out);
	  }
	m->pid2 = m_safe_fork(m);
	if (m->pid2 == 0)
		my_execve(m, pl);
	else
	{
        waitpid(m->pid2, NULL, 0);
        check_stdin_stdout(infile_token, outfile_token);
		close_fds(m->fd_in, m->fd_out);
	}
}
		// close(STDIN_FILENO); si je le close, le minishell s'arrete des que j'ai lancé une commande (comme ls)
		//close(STDOUT_FILENO); si je le close, les commandes simples finissent dans une entree infinie

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
	set_paths(minishell, minishell->envp_table);
	if (minishell->paths == NULL)
		return ;
	if (nb_cmds == 1)
		exec_one_cmd(minishell, minishell->process_list);
	else
		exec_several_cmds(minishell, minishell->process_list);
	wait_children_and_give_exit_status(minishell);
	
	dprintf(2, "I promise I'm not existing !\n");
	free(minishell->paths);
	free(minishell->process_list->good_path);
	ft_free_tab(minishell->process_list->tab_paths);
	//ft_free_node_process_list(minishell, minishell->process_list);
}
