/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_from_pipex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:45:16 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/29 09:47:10 by mbernard         ###   ########.fr       */
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
		ft_free_struct(m);
	ft_putendl_fd(msg, 2);
	exit(error_code);
}

void	print_name_and_exit_perror(t_minishell *m, char *name, int error_code)
{
	print_name(m, name);
	if (m != NULL)
		ft_free_struct(m);
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
