/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 08:17:34 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/18 22:56:13 by mbernard         ###   ########.fr       */
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

bool	ft_getenv(t_minishell *m, char dest[PATH_MAX], char *key)
{
	t_envp_list	*env;
	size_t		key_len;

	env = m->list_envp;
	key_len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->target, key, key_len) == 0)
		{
			ft_strlcpy(dest, env->value, ft_strlen(env->value) + 1);
			return (1);
		}
		env = env->next;
	}
	return (0);
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

void	join_with_old(t_minishell *m, char **split, t_envp_list **cpy,
		char *temp)
{
	temp = join_new_value_env_with_old(m, split, cpy);
	free(split[1]);
	split[1] = ft_strdup(temp);
	free(temp);
}

void	action_for_no_valid_key(char *arg, bool *check_key)
{
	print_cmd_perror_no_strerror(arg, "export: invalid identifier\n");
	*check_key = true;
}

bool add_var_or_value_to_envp_list(char **args, t_envp_list *env_variables, t_minishell *m, size_t index)
{
	bool check_key;
	char **split;

	split = NULL;
	check_key = false;
	while (args[index] != NULL)
	{
		if (ft_strchr(args[index], '=') == NULL)
			process_no_equal_sign(args[index], m, &check_key);
		else
		{
			split = ft_split(args[index], '=');
			if (split == NULL)
				exit_msg(m, "Malloc failed at export_variables", ENOMEM);
			if (is_valid_key_with_plus(split[0]) == false)
				action_for_no_valid_key(args[index], &check_key);
			else
				process_argument_with_equal_sign(m, env_variables, split);
			ft_free_tab(&split);
		}
		index++;
	}
	return (check_key);
}

