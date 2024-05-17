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
	} else
		return (export_variables(args + index, current, m));
	return (0);
}

/*static	bool	is_valid_key(char *key)
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
}*/

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
	char *content;

	content = NULL;
	if (split[1] == NULL)
	{
		content = ft_strdup("");
		if (content == NULL)
			exit_msg(m, "Malloc failed at add_var_or_value_to_envp_list", ENOMEM);
	}
	if (remove_env_var(&m->list_envp, split[0]) == MALLOC_FAILED)
		exit_msg(m, "Malloc failed at export_variables", ENOMEM);
	join_equal_sign(split);
	if (content)
	{
		if (add_new_envp(&m->list_envp, split[0], content) == MALLOC_FAILED)
			exit_msg(m, "Malloc failed at export_variables", ENOMEM);
	}
	else
	{
		if (add_new_envp(&m->list_envp, split[0], split[1]) == MALLOC_FAILED)
			exit_msg(m, "Malloc failed at export_variables", ENOMEM);
	}
	free(content);
}



void process_no_equal_sign(char *arg, t_minishell *m, bool *check_key)
{
	if (is_valid_env_var_key(arg) == false)
	{
		action_for_no_valid_key(arg, check_key);
		return;
	}
	if (remove_env_var(&m->list_envp, arg) == MALLOC_FAILED)
		exit_msg(m, "Malloc failed at export_variables", ENOMEM);
	if (add_new_envp(&m->list_envp, arg, NULL) == MALLOC_FAILED)
		exit_msg(m, "Malloc failed at export_variables", ENOMEM);
}

void process_argument_with_equal_sign(t_minishell *m, t_envp_list *env_variables, char **split)
{
	if (ft_strchr(split[0], '+') != NULL && split[1] != NULL)
		additionnal_env_content(m, &env_variables, split);
	else
		remove_and_add_envp(m, split);
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
