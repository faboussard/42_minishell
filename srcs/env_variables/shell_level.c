/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:34:09 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/24 16:43:53 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

void	increment_shell_level(t_envp_list **env_vars, t_minishell *m)
{
	t_envp_list	*env;
	char		*new_level;

	env = *env_vars;
	while (env && ft_strncmp(env->target, "SHLVL=", 6) != 0)
		env = env->next;
	if (env)
	{
		m->total_size_envp -= ft_strlen(env->value);
		if (ft_atoi(env->value) == 999)
			exit_msg(m, "Shell level too high", 1);
		if (ft_atoi(env->value) < 0)
			exit_msg(m, "Shell level too low", 1);
		new_level = ft_itoa(ft_atoi(env->value) + 1);
		if (new_level == NULL)
			exit_msg(m, "Malloc failed at shell_level", ENOMEM);
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
		if (ft_strncmp(env->target, "SHELL=", 6) == 0)
		{
			if (ft_strncmp(env->value, "minishell", 9) != 0)
			{
				free_safely_str(&env->value);
				env->value = ft_substr("minishell", 0, 9);
				break ;
			}
			else
			{
				increment_shell_level(env_vars, m);
				break ;
			}
		}
		env = env->next;
	}
}
