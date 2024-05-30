/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:45:16 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/30 17:50:42 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_name(t_minishell *m, char *name)
{
	char	*thename;

	thename = ft_strjoin("minishell: ", name);
	if (!thename)
		exit_msg(m, "Malloc error", ENOMEM);
	perror(thename);
	free_safely_str(&thename);
}

void	print_name_and_msg(t_minishell *m, char *name, char *msg)
{
	char	*the_name;
	char	*the_msg;
	char	*the_line_break;

	the_name = ft_strjoin("minishell: ", name);
	if (!the_name)
		exit_msg(m, "Malloc error", ENOMEM);
	the_msg = ft_strjoin(the_name, msg);
	free_safely_str(&the_name);
	if (!the_msg)
		exit_msg(m, "Malloc error", ENOMEM);
	the_line_break = ft_strjoin(the_msg, "\n");
	free_safely_str(&the_msg);
	if (!the_line_break)
		exit_msg(m, "Malloc error", ENOMEM);
	ft_putstr_fd(the_line_break, 2);
	free_safely_str(&the_line_break);
}

void	print_name_and_give_status(t_minishell *m, char *name, int err)
{
	print_name(m, name);
	m->status = err;
}
