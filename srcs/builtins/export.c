/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/02 18:02:37 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "utils.h"
#include "parser.h"
#include <readline/history.h>

int export_variables(char **args, t_envp_list *env_variables, t_minishell *m)
{
	size_t index;
	bool one_key_not_valid_return_1;

	one_key_not_valid_return_1 = false;
	index = 0;
	one_key_not_valid_return_1 = add_value_to_envp_list_if_valid(args, env_variables, m, index);
	if (one_key_not_valid_return_1 == true)
		return (1);
	else
		return (0);
}

char *join_new_value_env_with_old(t_envp_list **envp, char *value)
{
	char *tmp;
	char *new_value;

	tmp = ft_strdup((*envp)->value);
	if (!tmp)
		return (NULL);
	new_value = ft_strjoin(tmp, value);
	if (!new_value)
		return (NULL);
	free_safely_str(&tmp);
	return (new_value);
}


bool find_and_join_value(const char *tmp, t_envp_list **list, char *value)
{
	while ((*list))
	{
		if (ft_strncmp(tmp, (*list)->target, ft_strlen(tmp)) == 0)
		{
			if (!(*list)->value)
			{
				(*list)->value = ft_strdup(value);
				if (!(*list)->value)
				return (0);
			}
			else
			{
				if (!join_with_old(list, value))
					return (0);
			}
			break;
		}
		else
			(*list) = (*list)->next;
	}
	return (1);
}

char *additionnal_env_content(t_minishell *m, t_envp_list **env, char *key, char *value)
{
	char	*tmp;
	t_envp_list *cpy;

	cpy = *env;
	key = ft_memmove(key, key, ft_strlen(key) - 1);
	key[ft_strlen(key) - 1] = '\0';
	tmp = ft_strjoin(key, "=");
	if (!tmp)
	{
		free_safely_str(&key);
		free_safely_str(&value);
		exit_msg(m, "Malloc failed at get_env_var_index", ENOMEM);
	}
	if (!find_and_join_value(tmp, &cpy, value))
		exit_msg(m, "Malloc failed at get_env_var_index", ENOMEM);
	remove_and_add_envp(m, value, key);
	free_safely_str(&tmp);
	return (NULL);
}