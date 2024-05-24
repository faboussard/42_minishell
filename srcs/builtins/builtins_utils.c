/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 08:17:34 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/19 21:47:55 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

bool	contains_only_charset(const char *str, const char *charset)
{
	while (*str != '\0')
	{
		if (ft_strchr(charset, *str) == NULL)
			return (0);
		str++;
	}
	return (1);
}

static int	get_value_and_target(char *arg, char **value, char **key)
{
	int	j;

	if (arg == NULL)
		return (0);
	j = 0;
	while (arg[j] && arg[j] != '=')
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

static void	free_all(char *value, char *key)
{
	free_safely_str(&value);
	free_safely_str(&key);
}

static void	free_and_exit(t_minishell *m, char *value, char *key)
{
	free_all(value, key);
	exit_msg(m, "Malloc failed at make_export", ENOMEM);
}

bool	add_value_to_envp_list_if_valid(char **args, t_envp_list *env_variables,
										t_minishell *m, size_t index)
{
	bool	valid_key;
	char	*value;
	char	*key;

	valid_key = false;
	while (args[index] != NULL)
	{
		value = NULL;
		key = NULL;
		if (!ft_strncmp(args[index], "=", 1)
			|| !ft_strncmp(args[index], "+=", 2))
			return (print_error_export(args[index], &valid_key), valid_key);
		else if (get_value_and_target(args[index], &value, &key) == MALLOC_FAILED)
			free_and_exit(m, value, key);
		if (is_valid_key_with_plus(key) == false)
			print_error_export(args[index], &valid_key);
		else
			add_to_env(m, env_variables, value, key);
		free_all(value, key);
		index++;
	}
	return (valid_key);
}
