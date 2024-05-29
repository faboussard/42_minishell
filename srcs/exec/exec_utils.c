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
#include "signals.h"

void	close_pipes_and_fds(t_minishell *m, t_process_list *pl)
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

void	manage_signal_code(t_minishell *m, bool is_heredoc)
{
	if (WIFSIGNALED(m->status))
	{
		m->status = set_or_get_last_status(128 + WTERMSIG(m->status), 0);
		if (m->status == 131)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	}
	else if (WIFEXITED(m->status))
		m->status = WEXITSTATUS(m->status);
	else
		m->status = set_or_get_last_status(m->status, 0);
	if (is_heredoc)
	{
		if (m->status != 0)
			m->interrupted_here_doc = 1;
		else
			m->interrupted_here_doc = 0;
	}
}
