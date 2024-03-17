/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshells_list_generate.c                          :+:      :+:    :+:   */
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
	size_t	i;
	size_t	j;

	i = 0;
	while ((*envp)[i] && (*envp)[i] != '=')
		i++;
	((t_hashmap_node *)hm)->target = ft_substr(*envp, 0, i);
	if (((t_hashmap_node *)hm)->target == NULL)
		return (-1);
	j = i + 1;
	while ((*envp)[j] && (*envp)[j] != '=')
		j++;
	((t_hashmap_node *)hm)->content = ft_substr(*envp, j + 1, ft_strlen(*envp) - j);
	if (((t_hashmap_node *)hm)->content == NULL)
		return (-1);
	return (0);
}

int add_env_variable(t_hashmap hm, char **envp)
{
	char	*key;
	char	*value;

	while (*envp)
	{
		if (ft_strchr(*envp, '='))
		{
			if (get_target_and_content(envp, hm) == -1)
				return (-1);
			key = ((t_hashmap_node *) hm)->target;
			value = ((t_hashmap_node *) hm)->content;
			printf("key = %s, value = %s\n", key, value);
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