/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:45:16 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/04 08:34:48 by mbernard         ###   ########.fr       */
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
	if (m != NULL)
		ft_free_process_list(m, m->process_list);
	ft_putendl_fd(msg, 2);
	exit(error_code);
}

void	print_name_and_exit_perror(t_minishell *m, char *name, int error_code)
{
	print_name(m, name);
	if (m != NULL)
		ft_free_process_list(m, m->process_list);
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
	if (m != NULL)
		ft_free_process_list(m, m->process_list);
	exit_msg_minishell(m, "Malloc error", -1);
}

void	malloc_error_no_exit(t_minishell *m)
{
	ft_putstr_fd("Malloc error", 2);
	m->status = -1;
}
