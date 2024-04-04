/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:18:22 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/04 08:43:33 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	open_fd_infile(t_minishell *m, t_token_list *in_files_list)
{
	if (in_files_list->e_operator == HERE_DOC)
		m->fd_in = open("/tmp/.tmp_heredoc", O_RDONLY);
	else
		m->fd_in = open(in_files_list->name, O_RDONLY);
	if (m->fd_in < 0)
	{
		if (in_files_list->e_operator == HERE_DOC)
			print_name(m, "/tmp/.tmp_heredoc");
		else
			print_name(m, in_files_list->name);
		m->status = 1;
		m->process_list->dev_null = 1;
		m->fd_in = open("/dev/null", O_RDONLY);
		if (m->fd_in < 0)
			ft_putendl_fd("No /dev/null/ found", 2);
			/* exit_msg_pipex(NULL, "No /dev/null/ found", -1); */
			// A CHANGER, pas d'exit du minishell
			/*
			mbernard@z1r9p2:/usr$ cd cdvwev
			bash: cd: cdvwev: No such file or directory
			mbernard@z1r9p2:/usr$ echo $?
			1
			*/
	}
}

// MUSIQUE CAMELEON

void	open_fd_outfile(t_minishell *m, char *out)
{
	if (m->process_list->out_files_list->e_operator == INPUT_REDIRECT)
		m->fd_out = open(out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (m->process_list->out_files_list->e_operator == APPEND)
		m->fd_out = open(out, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (m->fd_out < 0)
		print_name_and_exit_perror(m, out, 1);
}
