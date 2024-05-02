/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "utils.h"
#include "parser.h"
#include <readline/history.h>

int ft_export(char **args, t_envp_list *env_variables, t_minishell *m)
{
	size_t	index;

	index = 1;
	if (args[index] == NULL)
	{
		if ((ft_lstsize_envp(env_variables)) <= 0)
			return (0);
		print_env_variables_export(&env_variables);
	}
	else
		return (export_variables(args + index, env_variables, m));
	return (0);
}

static	bool	is_valid_key(char *key)
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

char **change_value_if_plus(char **split, t_envp_list *env_variables, t_minishell *m)
{
	char *key;
	char *value;

	key = split[0];
	value = split[2];
	if (key[ft_strlen(key) - 1] == '+')
	{
		key = ft_substr(key, 0, ft_strlen(key) - 1);
		if (key == NULL)
			exit_msg(m, "Malloc failed at export_variables", 2);
		free(value);
		value = ft_strdup(return_env_content(m, &env_variables, key));
		if (value == NULL)
			return (NULL);
		remove_env_var(m, &env_variables, key);
	}
	return (split);
}

int export_variables(char **args, t_envp_list *env_variables, t_minishell *m)
{
	size_t index;
	char **split;
	bool one_key_not_valid_return_1;

	one_key_not_valid_return_1 = false;
	index = 0;

	while (args[index] != NULL)
	{
		split = ft_split(args[0], '=');
		if (is_valid_key(split[0]) == false)
		{
			print_cmd_perror_no_strerror(split[0], "export: invalid identifier\n");
			one_key_not_valid_return_1 = true;
			continue ;
		}
		split = change_value_if_plus(split, env_variables, m);
		create_env_variable(split, &env_variables, m);
		ft_free_all_tab(split);
		index++;
	}
	if (one_key_not_valid_return_1 == true)
		return (1);
	return (0);
}

char *return_env_content(t_minishell *minishell, t_envp_list **env, char *var)
{
	char	*tmp;
	t_envp_list *cpy;

	cpy = *env;
	tmp = ft_strjoin(var, "=");
	if (!tmp)
		exit_msg(minishell, "Malloc failed at get_env_var_index", 2);
	while (cpy)
	{
		if (ft_strncmp(tmp, (*env)->target, ft_strlen(tmp)) == 0)
			return ((*env)->value);
		else
			cpy = cpy->next;
	}
	free_safely_str(tmp);
	return (NULL);
}