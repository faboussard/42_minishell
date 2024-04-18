/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:26:23 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/18 14:55:27 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

void	set_current_path_with_cwd(t_minishell *m)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("minishell: getcwd");
		return ;
	}
	m->current_path = ft_strdup(cwd);
	if (m->current_path == NULL)
		ft_putendl_fd("minishell : malloc error", 2);
}

bool	set_env_var(t_minishell *m, char *target)
{
	t_envp_list *env;
	size_t var_len;

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
			return (1);
		}
		env = env->next;
	}
	return (0);
}