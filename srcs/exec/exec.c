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

#include "exec.h"
#include "signal.h"
#include "signals.h"

static void	exec_one_cmd(t_minishell *m, t_process_list *pl)
{
	ignore_signals();
	if (check_all_infiles(m, &pl) == 1 || create_all_outfiles(m, pl) == 1)
	{
		m->status = 1;
		close_fds(pl->fd_in, pl->fd_out);
		return ;
	}
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
	manage_signal_code(m, 0);
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
	delete_here_doc_files(m->pl);
	m->status = set_or_get_last_status(m->status, 0);
}
