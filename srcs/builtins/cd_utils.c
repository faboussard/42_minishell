/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:55:26 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/19 16:01:35 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

bool	ft_getenv(t_minishell *m, char dest[PATH_MAX], char *key)
{
	t_envp_list	*env;
	size_t		key_len;

	env = m->list_envp;
	key_len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->target, key, key_len) == 0)
		{
			ft_strlcpy(dest, env->value, ft_strlen(env->value) + 1);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

bool	should_go_home(char **cmd_table)
{
	if (cmd_table[1] == NULL)
		return (1);
	if (ft_strncmp(cmd_table[1], "~", 2) == 0)
		return (1);
	if (ft_strncmp(cmd_table[1], "~/", 3) == 0)
		return (1);
	return (0);
}
