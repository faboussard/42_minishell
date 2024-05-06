/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_care.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:22:26 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/06 14:38:22 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
close(m->fd_in); qui était dans first child dégage car cat | cat

void	fill_fd_with_emptiness(t_minishell *m, int *sad_fd)
{
	if (*sad_fd >= 0)
		close(*sad_fd);
	*sad_fd = open("/dev/null", O_RDONLY);
	if (*sad_fd < 0)
	{
		ft_putendl_fd("No /dev/null/ found", 2);
		m->status = 1;
	}
}
	if (pl->fd_out != STDOUT_FILENO)
	{
		m_safe_dup2(m, pl->fd_out, STDOUT_FILENO);
		close(pl->fd_out);
		close(m->pipe_fd[READ_END]);
		fill_fd_with_emptiness(m, pl->tmp_in);
	}
*/

static void	first_child(t_minishell *m, t_process_list *pl)
{
	handle_in_out(m, pl, &(pl->fd_in));
	if (pl->fd_in >= 0 && pl->fd_out >= 1 && pl->dev_null == 0)
	{
		m->pid1 = m_safe_fork(m);
		if (m->pid1 == 0)
		{
			m_safe_dup2(m, pl->fd_in, STDIN_FILENO);
			if (pl->fd_out != STDOUT_FILENO)
			{
				m_safe_dup2(m, pl->fd_out, STDOUT_FILENO);
				close(pl->fd_out);
			}
			else
				m_safe_dup2(m, m->pipe_fd[WRITE_END], STDOUT_FILENO);
			close_pipes(m->pipe_fd);
			my_execve(m, pl);
		}
		else
			close_and_redirect_pipe_to_stdin(m, pl);
	}
	else
		close_and_redirect_pipe_to_stdin(m, pl);
}

static void	last_child(t_minishell *m, t_process_list *pl)
{
	handle_in_out(m, pl, &(m->tmp_in));
	if (m->tmp_in >= 0 && pl->fd_out >= 1 && pl->dev_null == 0)
	{
		m->pid2 = m_safe_fork(m);
		if (m->pid2 == 0)
		{
			m_safe_dup2(m, m->tmp_in, STDIN_FILENO);
			close(m->tmp_in);
			if (pl->fd_out != STDOUT_FILENO)
			{
				m_safe_dup2(m, pl->fd_out, STDOUT_FILENO);
				close(pl->fd_out);
			}
			my_execve(m, pl);
		}
		else
			close_fds(m->tmp_in, pl->fd_out);
	}
	else
	{
		close_pipes(m->pipe_fd);
		close_fds(m->tmp_in, pl->fd_out);
	}
}

static void	middle_child(t_minishell *m, t_process_list *pl)
{
	handle_in_out(m, pl, &(m->tmp_in));
	if (pl->fd_in >= 0 && pl->fd_out >= 1 && pl->dev_null == 0)
	{
		m->pid1 = m_safe_fork(m);
		if (m->pid1 == 0)
		{
			m_safe_dup2(m, m->tmp_in, STDIN_FILENO);
			close(m->tmp_in);
			if (pl->fd_out != STDOUT_FILENO)
			{
				m_safe_dup2(m, pl->fd_out, STDOUT_FILENO);
				close(pl->fd_out);
			}
			else
				m_safe_dup2(m, m->pipe_fd[WRITE_END], STDOUT_FILENO);
			close_pipes(m->pipe_fd);
			my_execve(m, pl);
		}
		else
			close_and_redirect_pipe_to_stdin(m, pl);
	}
	else
		close_and_redirect_pipe_to_stdin(m, pl);
}

static void	wait_children_and_give_exit_status(t_minishell *m)
{
	int	status;

	status = 0;
	waitpid(m->pid2, &status, 0);
	while (waitpid(-1, NULL, 0) && errno != 10)
		;
	m->status = WEXITSTATUS(status);
}

void	exec_several_cmds(t_minishell *m, t_process_list *p_list)
{
	size_t			i;
	t_process_list	*pl;

	pl = p_list;
	if (safe_pipe(m) == 0)
		return ;
	first_child(m, pl);
	pl = pl->next;
	i = 1;
	while (++i < m->total_commands)
	{
		if (safe_pipe(m) == 0)
			return ;
		middle_child(m, pl);
		pl = pl->next;
	}
	last_child(m, pl);
	wait_children_and_give_exit_status(m);
	close_fds(pl->fd_in, pl->fd_out);
}

//	if (safe_pipe(m) == 0)
//		return ;
// --> pas besoin de safe_pipe dans le dernier enfant
/*
 *         if (pl->in_files_token->e_type== DELIMITER)
			here_doc(m, pl->in_files_token->name, STDIN_FILENO, &(m->tmp_in));
 * */

/*
void	handle_out(t_minishell *m, t_process_list *pl, int stdout, int *fd_out)
{
	enum e_token_type	outfile_token;

	outfile_token = pl->out_files_token->e_type;
	if (open_fd_outfile(m, pl, pl->out_files_token->name))
			return ;
		m_safe_dup2(m, *fd_out, stdout);
}
if (pl->in_files_token->e_type== DELIMITER)
		here_doc(m, pl->in_files_token->name, STDIN_FILENO, &(m->fd_in));
	if (open_fd_infile(m, pl->in_files_token))
		return ;
*/
