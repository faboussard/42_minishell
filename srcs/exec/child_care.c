/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_care.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:22:26 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/21 14:14:55 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//void	here_doc(t_minishell *m, char *limiter)
//{
//    check_and_delete_if_tmp_file_exists(HERE_DOC_TMP_FILE);
//    m->fd_in = open(HERE_DOC_TMP_FILE, O_CREAT | O_WRONLY | O_APPEND, 0666);
//    if (m->fd_in < 0)
//    {
//        perror("No /tmp/ directory found");
//        return ;
//    }
//    // A CHANGER, pas d'exit du minishell
//    m->pid1 = m_safe_fork(m);
//    if (m->pid1 == 0)
//        writing_in_heredoc(m, limiter);
//    else
//    {
//        while (waitpid(-1, &(m->status), 0) && errno != 10)
//            ;
//        close(m->fd_in);
//    }
//}

static void	first_child(t_minishell *m, t_process_list *pl)
{
	if (m->fd_in >= 0 && pl->dev_null == 0)
	{
		m->pid1 = m_safe_fork(m);
		if (m->pid1 == 0)
		{
			m_safe_dup2(m, m->fd_in, STDIN_FILENO);
			m_safe_dup2(m, m->pipe_fd[WRITE_END], STDOUT_FILENO);
			close(m->fd_in);
			close_pipes(m->pipe_fd);
//			if (!pl->cmd_table[0] || (!ft_strncmp(pl->cmd_table[0], "cat", 4)
//					&& !pl->cmd_table[1]))
//			here_cat(m);
 //           else
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
			if (m->fd_out != STDOUT_FILENO)
			{
				m_safe_dup2(m, m->fd_out, STDOUT_FILENO);
				close(m->fd_out);
			}
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
			close(m->pipe_fd[WRITE_END]);
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

void	exec_several_cmds(t_minishell *m, t_process_list *process_list)
{
	size_t			i;
	t_process_list	*pl;

	pl = process_list;
	if (safe_pipe(m) == 0)
		return ;
	if (open_fd_infile(m, pl->in_files_token))
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
	open_fd_outfile(m, pl, pl->out_files_token->name);
	if (safe_pipe(m) == 0)
		return ;
	last_child(m, pl);
	wait_children_and_give_exit_status(m);
	close_fds(m->fd_in, m->fd_out);
}
