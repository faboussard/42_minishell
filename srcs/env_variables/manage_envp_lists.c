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

void add_envp_to_list(t_envp_list **list_envp, t_envp_list *new_envp)
{
    if (new_envp == NULL)
        return;
    new_envp->next = *list_envp;
    *list_envp = new_envp;
}

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

bool	remove_env_var(t_minishell *minishell, int idx)
{
	int	i;
	int	count;

	if (idx > env_var_count(data->env))
		return (false);
	free_safely_str(minishell->env[idx]);
	i = idx;
	count = idx;
	while (minishell->env[i + 1])
	{
		minishell->env[i] = ft_strdup(minishell->env[i + 1]);
		free_safely_str(data->env[i + 1]);
		count++;
		i++;
	}
	minishell->env = realloc_env_vars(data, count);
	if (!minishell->env)
		return (false);
	return (true);
}
