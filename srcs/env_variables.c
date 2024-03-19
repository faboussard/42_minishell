/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c		                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

int get_target_and_content(char **envp, t_hashmap hm)
{
	size_t	i;
	char	*content;
	char	*target;

	i = 0;
	while ((*envp)[i] && (*envp)[i] != '=')
		i++;
	target = ft_substr(*envp, 0, i);
	if (target == NULL)
		return (-1);
	if ((*envp)[i] == '=')
	{
		i++;
		content = ft_substr(*envp, i, ft_strlen(*envp) - i);
		if (content == NULL)
		{
			free(target);
			return (-1);
		}
		if (ft_hm_add_elem(hm, target, content, &free) == -1)
		{
			free(target);
			free(content);
			return (-1);
		}
	}
	free(target);
	return (0);
}

int add_env_variable(t_hashmap hm, char **envp)
{
	if (envp == NULL || *envp == NULL)
		return (-1);
	while (*envp)
	{
		if (ft_strchr(*envp, '='))
		{
			if (get_target_and_content(envp, hm) == -1)
				return (-1);
		}
		envp++;
	}
	return (0);
}


t_hashmap get_hm_env_variables(char **envp)
{
	t_hashmap	env_variables;

	env_variables = ft_hm_init();
	if (env_variables == NULL)
		return (NULL);
	if (add_env_variable(env_variables, envp) == -1)
		return (ft_hm_clear(&env_variables, &free), NULL);
//	if (add_default_env_variables(env_variables) == -1)
//		return (ft_hm_clear(&env_variables, &free), NULL);
	return (env_variables);
}