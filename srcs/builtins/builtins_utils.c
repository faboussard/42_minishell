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

bool	is_valid_key_with_plus(char *key)
{
	size_t	index;

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

char *join_with_old(t_envp_list **list, char *content, t_minishell *m)
{
	char	*temp;
	char *temp2;
	char *new_content;

	temp = ft_strdup((*list)->value);
	if (temp == NULL)
		exit_msg(m, "Malloc failed at join_with_old", ENOMEM);
	temp2 = ft_strdup(content);
	if (temp2 == NULL)
	{
		free_safely_str(&temp);
		exit_msg(m, "Malloc failed at join_with_old", ENOMEM);
	}
	new_content = ft_strjoin(temp, temp2);
	free_safely_str(&temp);
	free_safely_str(&temp2);
	if (new_content == NULL)
		exit_msg(m, "Malloc failed at join_with_old", ENOMEM);
	return (new_content);
}

void	print_error_export(char *arg, bool *check_key)
{
	char *export_error;
	char *tmp;

	export_error = NULL;
	tmp = NULL;
	tmp = ft_strjoin("minishell: export: '", arg);
	if (!tmp)
	{
		ft_putstr_fd("Malloc failed at make_export\n", 2);
		return ;
	}
	export_error = ft_strjoin(tmp, "': not a valid identifier\n");
	if (!export_error)
	{
		free_safely_str(&tmp);
		ft_putstr_fd("Malloc failed at make_export\n", 2);
		return ;
	}
	ft_putstr_fd(export_error, 2);
	free_safely_str(&tmp);
	free_safely_str(&export_error);
	*check_key = true;
}

int	get_value_and_target(char *arg, char **value, char **key)
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

void	free_all(char *value, char *key)
{
	free_safely_str(&value);
	free_safely_str(&key);
}

void free_and_exit(t_minishell *m, char *value, char *key)
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
		if (ft_strncmp(args[index], "=", 1) == 0)
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
