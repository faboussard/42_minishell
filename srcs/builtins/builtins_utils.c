/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 08:17:34 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/19 12:05:30 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

bool contains_only_charset(const char *str, const char *charset)
{
	while (*str != '\0')
	{
		if (ft_strchr(charset, *str) == NULL)
			return (0);
		str++;
	}
	return (1);
}

bool is_valid_key_with_plus(char *key)
{
	size_t index;

	index = 0;
	if (!ft_isalpha(key[index]) && key[index] != '_')
		return (false);
	while (key[index] != '\0')
	{
		if (key[index] == '+' && key[index + 1] == '\0')
			return (true);
		if (!ft_isalnum(key[index]) && key[index] != '_')
			return (false);
		index++;
	}
	return (true);
}

bool join_with_old(t_envp_list **list, char *value)
{
	char *temp;

	temp = join_new_value_env_with_old(list, value);
	if (temp == NULL)
		return (0);
	free(value);
	value = ft_strdup(temp);
	if (value == NULL)
		return (0);
	free(temp);
	return (1);
}

void action_for_no_valid_key(char *arg, bool *check_key)
{
	print_cmd_perror_no_strerror(arg, "export: invalid identifier\n");
	*check_key = true;
}


int get_value_and_target(char *arg, char **value, char **key)
{
	int j;

	j = 0;
	while (arg[j] != '=')
		j++;
	*key = ft_substr(arg, 0, j);
	if (*key == NULL)
		return (MALLOC_FAILED);
	j++;
	*value = ft_substr(arg, j, ft_strlen(arg) - j);
	if (*value == NULL)
		return (MALLOC_FAILED);
	return (1);
}

void free_all(char **value, char **key)
{
	free_safely_str(value);
	free_safely_str(key);
}

bool add_value_to_envp_list_if_valid(char **args, t_envp_list *env_variables, t_minishell *m, size_t index)
{
	bool check_key;
	char *value;
	char *key;

	check_key = false;
	while (args[index] != NULL)
	{
		if (ft_strncmp(args[index], "=", 1) == 0)
		{
			check_key = true;
			action_for_no_valid_key(args[index], &check_key);
			return (check_key);
		}
		if (get_value_and_target(args[index], &value, &key) == MALLOC_FAILED)
			exit_msg(m, "Malloc failed at export_variables", ENOMEM);
		if (is_valid_key_with_plus(key) == false)
			action_for_no_valid_key(args[index], &check_key);
		else
			process_argument_with_equal_sign(m, env_variables, value, key);
		free_all(&value, &key);
		index++;
	}
	return (check_key);
}
