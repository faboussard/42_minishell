/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_care.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:22:26 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/28 14:41:52 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// close(m->fd_in); qui était dans first child dégage car cat | cat

static void	first_child(t_minishell *m, t_process_list *pl)
{
	if (m->fd_in >= 0 && pl->dev_null == 0)
	{
		m->pid1 = m_safe_fork(m);
		if (m->pid1 == 0)
		{
			m_safe_dup2(m, m->fd_in, STDIN_FILENO);
			if (m->fd_out != STDOUT_FILENO)
			{
				m_safe_dup2(m, m->fd_out, STDOUT_FILENO);
				close(m->fd_out);
			}
			else
				m_safe_dup2(m, m->pipe_fd[WRITE_END], STDOUT_FILENO);
			close_pipes(m->pipe_fd);
			my_execve(m, pl);
		}
		else
			close_and_redirect_pipe_to_stdin(m);
	}
	else
		close_and_redirect_pipe_to_stdin(m);
}

static void	last_child(t_minishell *m, t_process_list *pl)
{
	if (m->fd_out > 0)
	{
		m->pid2 = m_safe_fork(m);
		if (m->pid2 == 0)
		{
			close_pipes(m->pipe_fd);
			m_safe_dup2(m, m->tmp_in, STDIN_FILENO);
			my_execve(m, pl);
		}
		else
		{
			close_pipes(m->pipe_fd);
			close(m->tmp_in);
			close_fds(m->fd_in, m->fd_out);
		}
	}
	else
		close_pipes(m->pipe_fd);
}

void	fill_fd_with_emptiness(t_minishell *m, int full_fd)
{
	if (full_fd >= 0)
		close(full_fd);
	full_fd = open("/dev/null", O_RDONLY);
	if (full_fd < 0)
	{
		ft_putendl_fd("No /dev/null/ found", 2);
		m->status = 1;
	}
}

static void	middle_child(t_minishell *m, t_process_list *pl)
{
	if (m->fd_in >= 0)
	{
		m->pid1 = m_safe_fork(m);
		if (m->pid1 == 0)
		{
			m_safe_dup2(m, m->tmp_in, STDIN_FILENO);
			m_safe_dup2(m, m->pipe_fd[WRITE_END], STDOUT_FILENO);
			close_pipes(m->pipe_fd);
			my_execve(m, pl);
		}
		else
		{
			close(m->pipe_fd[WRITE_END]);
			if (m->fd_out != STDOUT_FILENO)
			{
				close(m->fd_out);
				close(m->pipe_fd[READ_END]);
				fill_fd_with_emptiness(m, m->tmp_in);
			}
		}
	}
	m_safe_dup2(m, m->pipe_fd[READ_END], m->tmp_in);
	close(m->pipe_fd[READ_END]);
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

void	handle_in(t_minishell *m, t_process_list *pl, int std_in, int *fd_in)
{
	enum e_token_type	infile_token;

	infile_token = pl->in_files_token->e_type;
	if (infile_token == DELIMITER)
		here_doc(m, pl->in_files_token->name, std_in, fd_in);
	if (open_fd_infile(m, pl->in_files_token))
		return ;
}

void	exec_several_cmds(t_minishell *m, t_process_list *p_list,
		int stdin_orig, int stdout_orig)
{
	size_t			i;
	t_process_list	*pl;

	pl = p_list;
	if (safe_pipe(m) == 0)
		return ;
	(void)stdout_orig;
	handle_in(m, pl, stdin_orig, &(m->fd_in));
	open_fd_outfile(m, pl, pl->out_files_token->name);
	first_child(m, pl);
	pl = pl->next;
	i = 1;
	while (++i < m->total_commands)
	{
		handle_in(m, pl, stdin_orig, &(m->tmp_in));
		open_fd_outfile(m, pl, pl->out_files_token->name);
		if (safe_pipe(m) == 0)
			return ;
		middle_child(m, pl);
		pl = pl->next;
	}
	handle_in(m, pl, stdin_orig, &(m->tmp_in));
	// handle_out(m, pl, STDOUT_FILENO, &(m->fd_out));
	open_fd_outfile(m, pl, pl->out_files_token->name);
	if (safe_pipe(m) == 0)
		return ;
	last_child(m, pl);
	wait_children_and_give_exit_status(m);
	close_fds(m->fd_in, m->fd_out);
}
/*
 *         if (pl->in_files_token->e_type== DELIMITER)
			here_doc(m, pl->in_files_token->name, stdin_orig, &(m->tmp_in));
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
		here_doc(m, pl->in_files_token->name, stdin_orig, &(m->fd_in));
	if (open_fd_infile(m, pl->in_files_token))
		return ;
*/