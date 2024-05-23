/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/02 17:47:09 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "utils.h"
#include "parser.h"
#include <readline/history.h>

int ft_export(char **args, t_envp_list **env_variables, t_minishell *m)
{
	size_t index;
	t_envp_list *current;

	index = 1;
	current = *env_variables;
	if (args[index] == NULL)
	{
		if ((ft_lstsize_envp(current)) <= 0)
			return (0);
		print_env_variables_export(m);
	}
	else
		return (make_export(args + index, current, m));
	return (0);
}

char *join_equal_sign(char *key)
{
	char *new_key;

	new_key = ft_strjoin(key, "=");
	if (new_key == NULL)
		return (NULL);
	return (new_key);
}

void free_export_strings(t_minishell *m, char **value, char **key)
{
	free_safely_str(key);
	free_safely_str(value);
	exit_msg(m, "Malloc failed at remove_and_add_envp", ENOMEM);
}



void remove_and_add_envp(t_minishell *m, char *value, char *key)
{
	char 		*key_with_equal_sign;

	key_with_equal_sign = join_equal_sign(key);
	if (key_with_equal_sign == NULL)
		free_export_strings(m, &value, &key);
	if (remove_env_var(&m->list_envp, key_with_equal_sign) == MALLOC_FAILED)
		free_export_strings(m, &value, &key);
	if (value[0] == '\0')
	{
		if (add_new_envp(&m->list_envp, key, value) == MALLOC_FAILED)
			free_export_strings(m, &value, &key);
	}
	else
	{
		if (add_new_envp(&m->list_envp, key_with_equal_sign, value) == MALLOC_FAILED)
			free_export_strings(m, &value, &key);
	}
	free_safely_str(&key_with_equal_sign);
}

void add_to_env(t_minishell *m, t_envp_list *env, char *value, char *key)
{
	char *joined_value;

	joined_value = NULL;
	if (ft_strchr(key, '+') != NULL && value != NULL)
	{
		key = ft_memmove(key, key, ft_strlen(key) - 1);
		key[ft_strlen(key) - 1] = '\0';
		joined_value = find_and_join_value(key, &env, value, m);
		remove_and_add_envp(m, joined_value, key);
		free_safely_str(&joined_value);
	}
	else
		remove_and_add_envp(m, value, key);
}