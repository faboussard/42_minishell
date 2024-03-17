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
#include "general.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "../libft/inc/libft.h"
#include "error.h"

int get_target_and_content(char **envp, t_hashmap hm)
{
	size_t i;

	i = 0;
	while ((*envp)[i] && (*envp)[i] != '=')
		i++;
	((t_hashmap_content *)hm)->target = ft_substr(*envp, 0, i);
	if (((t_hashmap_content *)hm)->target == NULL)
		return (-1);
	if ((*envp)[i] == '=')
	{
		i++;
		((t_hashmap_content *)hm)->content = ft_substr(*envp, i, ft_strlen(*envp) - i);
		if (((t_hashmap_content *)hm)->content == NULL)
			return (-1);
	}
	return (0);
}


int add_env_variable(t_hashmap hm, char **envp)
{
	char	*key;
	char	*value;

	if (envp == NULL || *envp == NULL)
		return (-1);
	while (*envp)
	{
		if (ft_strchr(*envp, '='))
		{
			if (get_target_and_content(envp, hm) == -1)
				return (-1);
			key = ((t_hashmap_content *) hm)->target;
			value = ((t_hashmap_content *) hm)->content;
			if (ft_hm_add_elem(hm, key, value, &free) == -1)
				return (ft_hm_clear(&hm, &free), -1);
			free(key);
			free(value);
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
		return (NULL);
	return (env_variables);
}