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
		return (export_variables(args + index, current, m));
	return (0);
}

void join_equal_sign(char *key)
{
	char *tmp;

	tmp = ft_strdup(key);
	free_safely_str(&key);
	key = ft_strjoin(tmp, "=");
	free_safely_str(&tmp);
}

void remove_and_add_envp(t_minishell *m, char *value, char *key)
{
	char *content;

	content = NULL;
	if (value == NULL)
	{
		content = ft_strdup("");
		if (content == NULL)
			exit_msg(m, "Malloc failed at add_value_to_envp_list_if_valid", ENOMEM);
	}
	if (remove_env_var(&m->list_envp, key) == MALLOC_FAILED)
		exit_msg(m, "Malloc failed at export_variables", ENOMEM);
	join_equal_sign(key);
	if (content)
	{
		if (add_new_envp(&m->list_envp, key, content) == MALLOC_FAILED)
			exit_msg(m, "Malloc failed at export_variables", ENOMEM);
	}
	else
	{
		if (add_new_envp(&m->list_envp, key, value) == MALLOC_FAILED)
			exit_msg(m, "Malloc failed at export_variables", ENOMEM);
	}
	free(content);
}

void process_argument_with_equal_sign(t_minishell *m, t_envp_list *env, char *value, char *key)
{
	if (ft_strchr(key, '+') != NULL && value != NULL)
		additionnal_env_content(m, &env, key, value);
	else
		remove_and_add_envp(m, value, key);
}