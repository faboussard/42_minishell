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
	one_key_not_valid_return_1 = add_var_to_envp_list(args, env_variables, m, index);
	if (one_key_not_valid_return_1 == true)
		return (1);
	return (0);
}

char *join_new_value_env_with_old(t_minishell *minishell, char *const *split, t_envp_list **envp)
{
	char *tmp;
	char *new_value;

	tmp = ft_strdup((*envp)->value);
	if (!tmp)
		exit_msg(minishell, "Malloc failed at get_env_var_index", 2);
	free((*envp)->value);
	new_value = ft_strjoin(tmp, split[1]);
	if (!new_value)
		exit_msg(minishell, "Malloc failed at get_env_var_index", 2);
	free(tmp);
	free(split[1]);
	return (new_value);
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
		exit_msg(m, "Malloc failed at get_env_var_index", 2);
	while (cpy)
	{
		if (ft_strncmp(tmp, cpy->target, ft_strlen(tmp)) == 0)
		{
			if (!cpy->value)
			{
				cpy->value = ft_strdup(split[1]);
				if (!cpy->value)
					exit_msg(m, "Malloc failed at get_env_var_index", 2);
			}
			else
			{
				split[1] = join_new_value_env_with_old(m, split, &cpy);
				break;
			}
		}
		else
			cpy = cpy->next;
	}
	join_equal_sign(split);
	remove_env_var(m, &m->list_envp, split[0]);
	add_new_envp(&m->list_envp, split[0], split[1]);
	free_safely_str(tmp);
	return (NULL);
}