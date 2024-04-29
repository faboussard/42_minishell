/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_table.c		                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <minishell.h>

t_envp_list *create_new_envp(char *target, char *content)
{
    t_envp_list *new_envp;

    new_envp = malloc(sizeof(t_envp_list));
    if (new_envp == NULL)
        return NULL;
    new_envp->target = ft_strdup(target);
    if (new_envp->target == NULL) {
        free(new_envp);
        return NULL;
    }
    if (content)
	{
        new_envp->value = ft_strdup(content);
        if (new_envp->value == NULL)
		{
			free_safely_str(new_envp->target);
            free(new_envp);
            return NULL;
        }
        new_envp->value_size = ft_strlen(new_envp->value);
    }
    new_envp->target_size = ft_strlen(new_envp->target);
    return (new_envp);
}

int	get_env_var_index(t_minishell *minishell, char **env, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		exit_msg(minishell, "Malloc failed at get_env_var_index", 2);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free_safely_str(tmp);
			return (i);
		}
		i++;
	}
	free_safely_str(tmp);
	return (-1);
}

char	*get_env_var_value(char **env, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free_safely_str(tmp);
			return (ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	free_safely_str(tmp);
	return (NULL);
}

int	env_var_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}


bool	remove_env_var(t_minishell *minishell, int idx)
{
	int	i;
	int	count;

	if (idx > env_var_count(minishell->envp_table))
		return (false);
	free_safely_str(minishell->envp_table[idx]);
	i = idx;
	count = idx;
	while (minishell->envp_table[i + 1])
	{
		minishell->envp_table[i] = ft_strdup(minishell->envp_table[i + 1]);
		free_safely_str(minishell->envp_table[i + 1]);
		count++;
		i++;
	}
//	minishell->envp_table = realloc_env_vars(data, count);
	if (!minishell->envp_table)
		return (false);
	return (true);
}
