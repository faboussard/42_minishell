/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:18:22 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/24 20:00:44 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static bool	handle_in(t_minishell *m, t_process_list *pl, int *fd_in)
{
	t_process_list	tmp;
	int				ret;

	if (pl && pl->in_files_list == NULL)
	{
		pl->fd_in = STDIN_FILENO;
		return (0);
	}
	tmp = *pl;
	while (tmp.in_files_list != NULL)
	{
		close_fds(*fd_in, 0);
		if (tmp.in_files_list->e_type == DELIMITER)
		{
			here_doc(m, tmp.in_files_list, fd_in, &pl);
			ret = open_fd_infile(m, pl, pl->here_doc_file, fd_in);
		}
		else
			ret = open_fd_infile(m, pl, tmp.in_files_list->name, fd_in);
		if (ret == 1)
			return (1);
		tmp.in_files_list = tmp.in_files_list->next;
	}
	return (0);
}

bool	handle_out(t_minishell *m, t_process_list *out)
{
	int	fd_out;

	if (out->out_files_list->e_type == APPEND_FILE)
		fd_out = open(out->out_files_list->name, O_CREAT | O_WRONLY | O_APPEND,
				0644);
	else
		fd_out = open(out->out_files_list->name, O_CREAT | O_WRONLY | O_TRUNC,
				0644);
	if (fd_out < 0)
	{
		print_name_and_give_status(m, out->out_files_list->name, 1);
		return (1);
	}
	close(fd_out);
	return (0);
}

static int	deals_with_no_outfile_case(t_minishell *m, t_process_list *pl)
{
	if (pl->next != NULL && (pl->next->in_files_list != NULL
			|| is_builtin(pl->next->cmd_table[0], pl->next->cmd_table)))
	{
		if (open_fd_outfile(m, pl, "/dev/null") == 1)
			return (1);
	}
	else
		pl->fd_out = STDOUT_FILENO;
	return (0);
}

int	handle_in_out(t_minishell *m, t_process_list *pl, int *fd_in)
{
	t_process_list	out;
	int				ret;

	if (handle_in(m, pl, fd_in))
		return (0);
	if (pl->out_files_list == NULL)
		return (deals_with_no_outfile_case(m, pl));
	out = *pl;
	while (out.out_files_list && out.out_files_list->next)
	{
		if (handle_out(m, &out))
			return (1);
		out.out_files_list = out.out_files_list->next;
	}
	if (out.out_files_list != NULL)
	{
		close_fds(pl->fd_out, 0);
		ret = open_fd_outfile(m, pl, out.out_files_list->name);
		if (ret == 1)
			return (1);
	}
	return (0);
}
