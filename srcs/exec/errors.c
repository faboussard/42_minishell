/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:45:16 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/18 13:59:40 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_name(t_minishell *m, char *name)
{
	char	*thename;

	thename = ft_strjoin("minishell: ", name);
	if (!thename)
		exit_msg_minishell(m, "Malloc error", -1);
	perror(thename);
	free(thename);
}

void	exit_command_not_found(t_minishell *m, char *name)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	exit_msg_minishell(m, "command not found", 127);
}

void	exit_msg_minishell(t_minishell *m, char *msg, int error_code)
{
	(void)m;
	ft_putendl_fd(msg, 2);
	exit(error_code);
}

void	print_name_and_exit_perror(t_minishell *m, char *name, int error_code)
{
	print_name(m, name);
	exit(error_code);
}

void	print_name_and_exit_msg(t_minishell *m, char *name, char *msg, int err)
{
	print_name(m, name);
	exit_msg_minishell(m, msg, err);
}

void	print_name_and_give_status(t_minishell *m, char *name, int err)
{
	print_name(m, name);
	m->status = err;
}

void	malloc_error_with_exit(t_minishell *m)
{
	exit_msg_minishell(m, "Malloc error", 1);
}

void	malloc_error_no_exit(t_minishell *m)
{
	ft_putstr_fd("Malloc error", 2);
	m->status = -1;
}
