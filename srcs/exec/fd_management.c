/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:18:22 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/24 09:59:38 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	manage_fd_error(t_minishell *m, t_process_list *pl, int *fd_to_use)
{
	if (pl->in_files_list->e_type == DELIMITER)
		perror("minishell: heredoc file can't be opened");
	else
		print_name(m, pl->in_files_list->name);
	m->status = 1;
	pl->dev_null = 1;
	*fd_to_use = open("/dev/null", O_RDONLY);
	if (*fd_to_use < 0)
		ft_putendl_fd("Couldn't open /dev/null/", 2);
}

int	open_fd_infile(t_minishell *m, t_process_list *pl, char *name,
		int *fd_to_use)
{
	enum e_token_type	infile_type;

	pl->dev_null = 0;
	if (pl->in_files_list != NULL)
	{
		if (pl->in_files_list->failed_expand == true)
		{
			print_name_and_msg(m, name, ": ambiguous redirect");
			return (1);
		}
		infile_type = pl->in_files_list->e_type;
		close_fds(*fd_to_use, 0);
		if (infile_type == DELIMITER)
			*fd_to_use = open(HERE_DOC_TMP_FILE, O_RDONLY);
		else if (infile_type == IN_FILE)
			*fd_to_use = open(name, O_RDONLY);
	}
	else
		pl->fd_in = STDIN_FILENO;
	if (*fd_to_use < 0)
	{
		manage_fd_error(m, pl, fd_to_use);
		return (1);
	}
	return (0);
}

int	open_fd_outfile(t_minishell *m, t_process_list *pl, char *out)
{
	t_process_list tmp;

	if (pl->out_files_list != NULL)
	{
		tmp = *pl;
		while (tmp.out_files_list->next)
			tmp.out_files_list = tmp.out_files_list->next;
		if (tmp.out_files_list->e_type == OUT_FILE)
			pl->fd_out = open(out, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		else if (tmp.out_files_list->e_type == APPEND_FILE)
			pl->fd_out = open(out, O_CREAT | O_WRONLY | O_APPEND, 0664);
	}
	else if (pl->next != NULL && ft_strncmp(out, "/dev/null", 10) == 0)
		pl->fd_out = open("/dev/null", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	else
		pl->fd_out = STDOUT_FILENO;
	if (pl->fd_out < 0)
	{
		print_name_and_give_status(m, out, 1);
		return (1);
	}
	return (0);
}

bool	handle_in(t_minishell *m, t_process_list *pl, int *fd_in)
{
	t_process_list	tmp;
	int				ret;

	if (pl->in_files_list == NULL)
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
			here_doc(m, pl->in_files_list, fd_in, pl);
			ret = open_fd_infile(m, pl, HERE_DOC_TMP_FILE, fd_in);
		}
		else
			ret = open_fd_infile(m, pl, tmp.in_files_list->name, fd_in);
		if (ret == 1)
			return (1);
		tmp.in_files_list = tmp.in_files_list->next;
	}
	return (0);
}

bool	is_builtin(char *cmd, char **cmd_table)
{
	if (!cmd || !cmd_table)
		return (0);
	if (cmd && ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	else if (cmd && ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	else if (cmd && ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (cmd && ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	else if (cmd && ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	else if (cmd && ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	else if (cmd && ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	else
		return (0);
}

int	deals_with_no_outfile_case(t_minishell *m, t_process_list *pl) {
	if (pl->next != NULL && (pl->next->in_files_list != NULL
							 || is_builtin(pl->next->cmd_table[0],
										   pl->next->cmd_table))) {
		if (open_fd_outfile(m, pl, "/dev/null") == 1)
			return (1);
	} else
		pl->fd_out = STDOUT_FILENO;
	return (0);
}

int	handle_in_out(t_minishell *m, t_process_list *pl, int *fd_in)
{
	t_process_list	out;
	int				fd_out;
	int				ret;

	if (handle_in(m, pl, fd_in))
		return (0);
	if (pl->out_files_list == NULL)
		return (deals_with_no_outfile_case(m, pl));
	out = *pl;
	while (out.out_files_list && out.out_files_list->next)
	{
		if (out.out_files_list->e_type == APPEND_FILE)
			fd_out = open(out.out_files_list->name,
						  O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd_out = open(out.out_files_list->name,
						  O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			print_name_and_give_status(m, out.out_files_list->name, 1);
			return (1);
		}
		close(fd_out);
		out.out_files_list = out.out_files_list->next;
	}
	if (out.out_files_list != NULL)
	{
		close_fds(pl->fd_out, 0);
		ret = open_fd_outfile(m, pl, out.out_files_list->name);
		if (ret == 1)
			return (1);
		out.out_files_list = out.out_files_list->next;
	}
	return (0);
}

void	close_and_redirect_pipe_to_stdin(t_minishell *m, t_process_list *pl)
{
	if (m->pipe_fd[WRITE_END] > 0)
		close(m->pipe_fd[WRITE_END]);
	if (pl->fd_in >= 3)
		close(pl->fd_in);
	if (m->tmp_in >= 3)
		close(m->tmp_in);
	m->tmp_in = m->pipe_fd[READ_END];
	if (pl->fd_out != STDOUT_FILENO)
		close(pl->fd_out);
}