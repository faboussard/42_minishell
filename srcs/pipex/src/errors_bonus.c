/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:37:40 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/25 15:43:34 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	print_name(t_pipex *p, char *name)
{
	char	*thename;

	thename = ft_strjoin("pipex: ", name);
	if (!thename)
		exit_msg(p, "Malloc error", -1);
	perror(thename);
	free(thename);
}

void	exit_command_not_found(t_pipex *p, char *name)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	exit_msg(p, "command not found", 127);
}

void	exit_msg(t_pipex *p, char *msg, int error_code)
{
	if (p != NULL)
		ft_free_struct(p);
	ft_putendl_fd(msg, 2);
	exit(error_code);
}

void	print_name_and_exit_perror(t_pipex *p, char *name, int error_code)
{
	print_name(p, name);
	if (p != NULL)
		ft_free_struct(p);
	exit(error_code);
}

void	print_name_and_exit_msg(t_pipex *p, char *name, char *msg, int err)
{
	print_name(p, name);
	exit_msg(p, msg, err);
}
