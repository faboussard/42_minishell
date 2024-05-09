/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:26:23 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/09 16:41:22 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include "exec.h"


void create_3_env_variables(t_minishell *m)
{
	char PWD[PATH_MAX];
	if (add_new_envp(&m->list_envp,"_=", "/usr/bin/env"))
		exit_msg_minishell(m, "Malloc failed at create_3_env_variables", -1);
	m->total_size_envp += ft_strlen("_=") + ft_strlen("/usr/bin/env");
	if (add_new_envp(&m->list_envp, "SHLVL=", "1"))
		exit_msg_minishell(m, "Malloc failed at create_3_env_variables", -1);
	m->total_size_envp += ft_strlen("SHLVL") + ft_strlen("1");
	if (getcwd(PWD, sizeof(PWD)) == NULL)
	{
		perror("minishell: getcwd");
		ft_strlcpy(PWD, "/home/goinfre/faboussa", 22);
	}	
	if (add_new_envp(&m->list_envp, "PWD=", PWD))
		exit_msg_minishell(m, "Malloc failed at create_3_env_variables", -1);
	m->total_size_envp += ft_strlen("PWD=") + ft_strlen(PWD);
}