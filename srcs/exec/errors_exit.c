/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:06:48 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/03 17:14:54 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exit_command_not_found(t_minishell *m, char *name, t_process_list *pl)
{
	char *msg;

	msg = ft_strjoin(name, ": command not found");
	if (!msg)
		malloc_error_with_exit(m);
	//free_safely_str(&name);
	ft_putendl_fd(msg, 2);
	free_safely_str(&msg);
	ft_free_pl_paths(m, pl);
	free_minishell(m);
	exit(127);
}

void	exit_is_a_directory(t_minishell *m, char *name, t_process_list *pl)
{
	char *msg;
	char	*tmp;

	if (access(pl->cmd_table[0], F_OK) != 0
		|| (access(pl->cmd_table[0], F_OK) == 0
		&& access(pl->cmd_table[0], X_OK) != 0))
	{
		print_name(m, pl->cmd_table[0]);
		ft_free_pl_paths(m, pl);
		free_minishell(m);
		if (errno == 13)
			exit(126);
		exit(127);
	}
	tmp = ft_strjoin("minishell: ", name);
	if (!tmp)
		malloc_error_with_exit(m);
	msg = ft_strjoin(tmp, ": Is a directory");
	free_safely_str(&tmp);
	if (!msg)
		malloc_error_with_exit(m);
	//	free_safely_str(&name);
	ft_putendl_fd(msg, 2);
	free_safely_str(&msg);
	ft_free_pl_paths(m, pl);
	free_minishell(m);
	exit(126);
}

/*void	exit_no_such_file_or_dir(t_minishell *m, char *name, t_process_list *pl)
{
	char *msg;
	char	*tmp;

	tmp = ft_strjoin("minishell: ", name);
	if (!tmp)
		malloc_error_with_exit(m);
	msg = ft_strjoin(tmp, ": No such file or directory");
	free_safely_str(&tmp);
	if (!msg)
		malloc_error_with_exit(m);
	//	free_safely_str(&name);
	ft_putendl_fd(msg, 2);
	free_safely_str(&msg);
	ft_free_pl_paths(m, pl);
	free_minishell(m);
	exit(127);
}*/

void	exit_msg_minishell(t_minishell *m, char *msg, int error_code)
{
	ft_putendl_fd(msg, 2);
	if (m != NULL)
		free_minishell(m);
	exit(error_code);
}

void	print_name_and_exit_perror(t_minishell *m, char *name, int error_code)
{
	print_name(m, name);
	free_safely_str(&name);
	free_minishell(m);
	exit(error_code);
}

void	print_name_and_exit_msg(t_minishell *m, char *name, char *msg, int err)
{
	print_name(m, name);
	exit_msg_minishell(m, msg, err);
}

void	malloc_error_with_exit(t_minishell *m)
{
	exit_msg_minishell(m, "Malloc error", ENOMEM);
}
