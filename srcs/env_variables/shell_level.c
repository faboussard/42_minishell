/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:34:09 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/09 20:08:58 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

void	increment_shell_level(t_envp_list **env_vars, t_minishell *m)
{
	t_envp_list *env;
	char *new_level;

	env = *env_vars;
	while (env && ft_strncmp(env->target, "SHLVL=", 6) != 0)
		env = env->next;
	if (env)
	{
		m->total_size_envp -= ft_strlen(env->value);
		new_level = ft_itoa(ft_atoi(env->value) + 1);
		if (new_level == NULL)
			exit_msg(m, "Malloc failed at increment_shell_level", 2);
		free_safely_str(&env->value);
		env->value = new_level;
		m->total_size_envp += ft_strlen(new_level);
	}
}

void	assign_shell_and_shell_level(t_envp_list **env_vars, t_minishell *m)
{
	t_envp_list	*env;

	env = *env_vars;
	while (env)
	{
		if (env && ft_strncmp(env->target, "SHELL=", 6) == 0)
		{
			if (ft_strncmp(env->value, "minishell", 9) != 0)
			{
				free_safely_str(&env->value);
				env->value = ft_substr("minishell", 0, 9);
			}
			else
				increment_shell_level(env_vars, m);
		}
		env = env->next;
	}
}