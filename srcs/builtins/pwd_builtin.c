/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:32:23 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/18 14:35:01 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

bool	print_env_var(t_minishell *m, char *var)
{
	t_envp_list	*env;
	size_t		var_len;

	env = m->list_envp;
	var_len = ft_strlen(var);
	while (env && env->next)
	{
		if (ft_strncmp(env->target, var, var_len) == 0)
		{
			ft_putendl_fd(env->value, 1);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	ft_pwd(t_minishell *minishell)
{
	char	cwd[PATH_MAX];

	if (print_env_var(minishell, "PWD="))
		return (0);
	if (minishell->current_path != NULL)
	{
		printf("%s\n", minishell->current_path);
		return (0);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("minishell: getcwd");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
