/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:06:48 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/24 20:01:38 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"

void	exit_command_not_found(t_minishell *m, char *name, t_process_list *pl,
		bool to_free)
{
	char	*msg;

	msg = ft_strjoin(name, ": command not found");
	if (to_free)
		free_safely_str(&name);
	if (!msg)
		exit_msg(m, "Malloc error in error exit", ENOMEM);
	ft_putendl_fd(msg, 2);
	free_safely_str(&msg);
	ft_free_pl_paths(m, pl);
	free_minishell(m);
	exit(127);
}

static void	handle_if_exist_but_not_exec(t_minishell *m, t_process_list *pl)
{
	if (access(pl->cmd_table[0], F_OK) == 0
		&& access(pl->cmd_table[0], X_OK) != 0)
	{
		print_name(m, pl->cmd_table[0]);
		ft_free_pl_paths(m, pl);
		free_minishell(m);
		exit(126);
	}
}

void	exit_is_a_directory(t_minishell *m, char *name, t_process_list *pl)
{
	char	*msg;
	char	*tmp;

	handle_if_exist_but_not_exec(m, pl);
	if (access(pl->cmd_table[0], F_OK) != 0)
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
		exit_msg(m, "Malloc error in error exit", ENOMEM);
	msg = ft_strjoin(tmp, ": Is a directory");
	free_safely_str(&tmp);
	if (!msg)
		exit_msg(m, "Malloc error in error exit", ENOMEM);
	ft_putendl_fd(msg, 2);
	free_safely_str(&msg);
	ft_free_pl_paths(m, pl);
	free_minishell(m);
	exit(126);
}

void	exit_msg(t_minishell *m, char *msg, int error_code)
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
