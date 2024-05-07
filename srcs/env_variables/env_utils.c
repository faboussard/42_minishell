/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:26:23 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/22 08:45:43 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include "exec.h"

void	set_current_path_with_cwd(t_minishell *m)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("minishell: getcwd");
		return ;
	}
	ft_strlcpy(m->current_path, cwd, ft_strlen(cwd) + 1);
}

bool	set_env_var(t_minishell *m, char **var, char *target)
{
	t_envp_list	*env;
	size_t		target_len;

	env = m->list_envp;
	target_len = ft_strlen(target);
	while (env && env->next)
	{
		if (ft_strncmp(env->target, target, target_len) == 0)
		{
			ft_strlcpy(*var, env->value, ft_strlen(env->value) + 1);
			if (var == NULL)
			{
				ft_putendl_fd("minishell : malloc error", 2);
				return (0);
			}
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	set_minishell_paths(t_minishell *m)
{
	char	*current_path;
	char	*old_pwd;

	current_path = m->current_path;
	old_pwd = m->old_pwd;
	if (set_env_var(m, &current_path, "PWD=") == 0)
		set_current_path_with_cwd(m);
	if (set_env_var(m, &old_pwd, "OLDPWD=") == 0)
		ft_strlcpy(m->old_pwd, m->current_path, ft_strlen(m->current_path) + 1);
}
/*
bool	set_env_var(t_minishell *m, char *var, char *target)
{
	t_envp_list	*env;
	size_t		var_len;

	env = m->list_envp;
	var_len = ft_strlen(target);
	while (env && env->next)
	{
		if (ft_strncmp(env->target, target, var_len) == 0)
		{
			m->current_path = ft_strdup(env->value);
			if (m->current_path == NULL)
			{
				ft_putendl_fd("minishell : malloc error", 2);
				return (0);
			}
			ft_putendl_fd(m->current_path, 2);
			return (1);
		}
		env = env->next;
	}
	return (0);
}
*/