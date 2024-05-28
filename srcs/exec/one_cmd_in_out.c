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

int	check_all_infiles(t_minishell *m, t_process_list *pl)
{
	t_process_list	tmp;
	int				fd_in;

	if (pl->in_files_list == NULL)
		return (0);
	tmp = *pl;
	fd_in = 0;
	while (tmp.in_files_list && tmp.in_files_list->next)
	{
		if (tmp.in_files_list->e_type == DELIMITER)
			here_doc(m, tmp.in_files_list, &fd_in, &tmp);
		if (open_fd_infile(m, &tmp, tmp.in_files_list->name, &fd_in) == 0)
			close(fd_in);
		else
			return (1);
		tmp.in_files_list = tmp.in_files_list->next;
	}
	if (tmp.in_files_list && tmp.in_files_list->e_type == DELIMITER)
	{
		here_doc(m, tmp.in_files_list, &(pl->fd_in), &tmp);
		pl->here_doc_file = tmp.here_doc_file;
	}
	if (tmp.in_files_list
		&& open_fd_infile(m, &tmp, tmp.in_files_list->name, &(pl->fd_in)))
		return (1);
	return (0);
}

int	create_all_outfiles(t_minishell *m, t_process_list *pl)
{
	t_process_list	tmp;

	if (pl->out_files_list == NULL)
		return (0);
	tmp = *pl;
	while (tmp.out_files_list && tmp.out_files_list->next)
	{
		if (handle_out(m, &tmp))
			return (1);
		tmp.out_files_list = tmp.out_files_list->next;
	}
	if (tmp.out_files_list)
	{
		if (open_fd_outfile(m, pl, tmp.out_files_list->name) == 1)
			return (1);
	}
	return (0);
}

int	handle_infile_outfile(t_minishell *m, t_process_list *pl)
{
	if (pl->in_files_list != NULL)
	{
		m_safe_dup2(m, pl->fd_in, STDIN_FILENO);
		close(pl->fd_in);
	}
	if (pl->out_files_list != NULL)
	{
		m_safe_dup2(m, pl->fd_out, STDOUT_FILENO);
		close(pl->fd_out);
	}
	return (0);
}
