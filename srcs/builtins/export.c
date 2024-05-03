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
	one_key_not_valid_return_1 = add_var_or_value_to_envp_list(args, env_variables, m, index);
	if (one_key_not_valid_return_1 == true)
		return (1);
	else
		return (0);
}

char *join_new_value_env_with_old(t_minishell *m, char **split, t_envp_list **envp)
{
	char *tmp;
	char *new_value;

	tmp = ft_strdup((*envp)->value);
	if (!tmp)
	{
		ft_free_tab(&split);
		exit_msg(m, "Malloc failed at get_env_var_index", 2);
	}
	new_value = ft_strjoin(tmp, split[1]);
	if (!new_value)
	{
		ft_free_tab(&split);
		exit_msg(m, "Malloc failed at get_env_var_index", 2);
	}
	free(tmp);
	return (new_value);
}


void find_and_join_value(t_minishell *m, char **split, const char *tmp, t_envp_list **cpy)
{
	char *temp;

	temp = NULL;
	while ((*cpy))
	{
		if (ft_strncmp(tmp, (*cpy)->target, ft_strlen(tmp)) == 0)
		{
			if (!(*cpy)->value)
			{
				(*cpy)->value = ft_strdup(split[1]);
				if (!(*cpy)->value)
				{
					ft_free_tab(&split);
					exit_msg(m, "Malloc failed at get_env_var_index", 2);
				}
			}
			else
				join_with_old(m, split, cpy, temp);
			break;
		}
		else
			(*cpy) = (*cpy)->next;
	}
}

char *additionnal_env_content(t_minishell *m, t_envp_list **env, char **split)
{
	char	*tmp;
	t_envp_list *cpy;

	cpy = *env;
	split[0] = ft_memmove(split[0], split[0], ft_strlen(split[0]) - 1);
	split[0][ft_strlen(split[0]) - 1] = '\0';
	tmp = ft_strjoin(split[0], "=");
	if (!tmp)
	{
		ft_free_tab(&split);
		exit_msg(m, "Malloc failed at get_env_var_index", 2);
	}
	find_and_join_value(m, split, tmp, &cpy);
	remove_and_add_envp(m, split);
	free_safely_str(tmp);
	return (NULL);
}