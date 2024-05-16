/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:45:16 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/03 17:14:54 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_name(t_minishell *m, char *name)
{
	char	*thename;

	thename = ft_strjoin("minishell: ", name);
	if (!thename)
		exit_msg_minishell(m, "Malloc error", ENOMEM);
	perror(thename);
	free_safely_str(&thename);
}

void	print_name_and_give_status(t_minishell *m, char *name, int err)
{
	print_name(m, name);
	m->status = err;
}

void	malloc_error_no_exit(t_minishell *m)
{
	ft_putstr_fd("Malloc error", ENOMEM);
	m->status = -1;
}
