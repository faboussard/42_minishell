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
	size_t	index;
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
		return (export_variables(args + index, current, m));
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

void join_equal_sign(char **split)
{
	char *tmp;

	tmp = ft_strdup(split[0]);
	free_safely_str(&(split[0]));
	split[0] = ft_strjoin(tmp, "=");
	free_safely_str(&tmp);
}

void remove_and_add_envp(t_minishell *m, char **split)
{
	if (split[1] != NULL)
		join_equal_sign(split);
	remove_env_var(m, &m->list_envp, split[0]);
	add_new_envp(&m->list_envp, split[0], split[1]);
}

bool add_var_or_value_to_envp_list(char **args, t_envp_list *env_variables, t_minishell *m, size_t index)
{
	char **split;
	bool one_key_not_valid_return_1;
	split = NULL;

	one_key_not_valid_return_1 = false;
	while (args[index] != NULL)
	{
		split = ft_split(args[index], '=');
		if (split == NULL)
			exit_msg(m, "Malloc failed at export_variables", 2);
		if (is_valid_key(split[0]) == false)
		{
			print_cmd_perror_no_strerror(split[0], "export: invalid identifier\n");
			one_key_not_valid_return_1 = true;
			index++;
			continue ;
		}
		if (ft_strchr(split[0], '+') != NULL && split[1] != NULL)
			additionnal_env_content(m, &env_variables, split);
		else
			remove_and_add_envp(m, split);
		ft_free_tab(&split);
		index++;
	}
	return (one_key_not_valid_return_1);
}