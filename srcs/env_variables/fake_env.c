/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:26:23 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/24 16:53:30 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "utils.h"

void	create_3_env_variables(t_minishell *m)
{
	char	pwd[PATH_MAX];

	if (add_new_envp(&m->list_envp, "_=", "/usr/bin/env"))
		exit_msg_minishell(m, "Malloc failed at fake_env", ENOMEM);
	m->total_size_envp += ft_strlen("_=") + ft_strlen("/usr/bin/env");
	if (add_new_envp(&m->list_envp, "SHLVL=", "1"))
		exit_msg_minishell(m, "Malloc failed at fake_env", ENOMEM);
	m->total_size_envp += ft_strlen("SHLVL") + ft_strlen("1");
	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("minishell: getcwd");
		ft_strlcpy(pwd, "/home/goinfre/faboussa", 22);
	}
	if (add_new_envp(&m->list_envp, "PWD=", pwd))
		exit_msg_minishell(m, "Malloc failed at fake_env", ENOMEM);
	m->total_size_envp += ft_strlen("PWD=") + ft_strlen(pwd);
}
