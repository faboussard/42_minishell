/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_table.c		                            :+:      :+:    :+:   */
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

int get_target_and_content(char **envp, t_dict envp_dict)
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
		if (ft_hm_add_elem(envp_dict, target, content, &free) == -1)
		{
			free(target);
			free(content);
			return (-1);
		}
	}
	free(target);
	return (0);
}

t_dict	ft_dict_init(void)
{
	return (ft_calloc(HASHMAP_ARR_SIZE, sizeof(t_dict)));
}

int create_dict_env_variable(char **envp, t_dict dict_chain)
{
	while (*envp)
	{
		if (ft_strchr(*envp, '='))
		{
			if (get_target_and_content(envp, dict_chain) == -1)
				return (-1);
		}
		envp++;
	}
	return (0);
}

t_hashmap_struct *create_dict_envp(char **envp)
{
	t_hashmap_struct *hashmap_environment;

	hashmap_environment = (t_hashmap_struct *)ft_calloc(1, sizeof(t_hashmap_struct));
	if (hashmap_environment == NULL)
		return NULL;
	hashmap_environment->dict_chain = ft_dict_init();
	if (hashmap_environment->dict_chain == NULL)
	{
		free(hashmap_environment);
		return (NULL);
	}
	if (create_dict_env_variable(envp, hashmap_environment->dict_chain) == -1)
	{
		ft_hm_clear(&hashmap_environment->dict_chain, &free);
		free(hashmap_environment);
		return (NULL);
	}
	return (hashmap_environment);
}
