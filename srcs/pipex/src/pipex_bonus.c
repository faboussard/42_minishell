/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:03:42 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/25 16:35:30 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	open_and_check_fd_infile(t_pipex *p, char *in)
{
	if (p->here_doc == 0)
		p->fd_in = open(in, O_RDONLY);
	else if (p->here_doc == 1)
		p->fd_in = open("/tmp/.tmp_heredoc", O_RDONLY);
	if (p->fd_in < 0)
	{
		print_name(p, in);
		p->status = 1;
		p->dev_null = 1;
		p->fd_in = open("/dev/null", O_RDONLY);
		if (p->fd_in < 0)
			exit_msg(NULL, "No /dev/null/ found", -1);
	}
}

void	open_and_check_fd_outfile(t_pipex *p, char *out)
{
	if (p->here_doc == 0)
		p->fd_out = open(out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (p->here_doc == 1)
		p->fd_out = open(out, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (p->fd_out < 0)
		print_name_and_exit_perror(p, out, 1);
}

void	exec(t_pipex *p, char *cmd, char **env)
{
	char	*entire_cmd;
	size_t	skip_first;

	set_good_path_with_cmd(p, cmd);
	skip_first = 0;
	while (cmd[skip_first] && cmd[skip_first] != ' ')
		skip_first++;
	entire_cmd = join_sep(p, p->good_path, cmd + skip_first, ' ');
	ft_free_tab(p->cmd_args);
	set_cmd_args(p, entire_cmd);
	erase_spaces_in_cmd_args(p);
	free(entire_cmd);
	if (p->cmd_args == NULL)
		exit_msg(p, "Malloc error", -1);
	execve(p->good_path, p->cmd_args, env);
	if (access(p->good_path, F_OK) == 0)
		print_name_and_exit_perror(p, p->cmd_args[0], 1);
	else
		exit_command_not_found(p, p->cmd_args[0]);
}

static int	wait_children_and_give_the_exit_status_please(t_pipex *p)
{
	int	status;

	while (waitpid(p->pid2, &status, 0) && errno != 10)
		;
	while (waitpid(-1, &(p->status), 0) && errno != 10)
		;
	return (status);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;
	int		error_status;
	int		i;

	if (ac >= 5)
	{
		i = 2;
		ft_init_struct(&pipex);
		if (is_here_doc(&pipex, av[1]))
			handle_heredoc(&pipex, av[2], &i, ac);
		check_null_cmd(ac, av, i);
		open_and_check_fd_infile(&pipex, av[1]);
		set_paths(&pipex, env);
		child_care(&pipex, av[i], env, 1);
		while (++i < ac - 2)
			child_care(&pipex, av[i], env, 2);
		open_and_check_fd_outfile(&pipex, av[ac - 1]);
		child_care(&pipex, av[i], env, 3);
		error_status = wait_children_and_give_the_exit_status_please(&pipex);
		pipex.status = WEXITSTATUS(error_status);
		ft_free_struct(&pipex);
	}
	else if (ac < 5)
		exit_msg(NULL, "Invalid number of arguments", 1);
	return (pipex.status);
}
