/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:18:22 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/29 09:54:26 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	open_fd_infile(t_minishell *m, char *in)
{
	if (m->here_doc == 1)
	{
		check_and_delete_if_tmp_file_exists("/tmp/.tmp_heredoc");
		m->fd_in = open("/tmp/.tmp_heredoc", O_RDONLY);
	}
	else
		m->fd_in = open(in, O_RDONLY);
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
