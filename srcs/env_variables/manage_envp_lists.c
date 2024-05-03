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

#include "parser.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <minishell.h>

t_envp_list *allocate_envp_node()
{
	t_envp_list *new_envp;

	new_envp = ft_calloc(1, sizeof(t_envp_list));
	if (new_envp == NULL)
		return (NULL);
	new_envp->target = NULL;
	new_envp->value = NULL;
	new_envp->target_size = 0;
	new_envp->value_size = 0;
	return (new_envp);
}

bool initialize_envp_node(t_envp_list *new_envp, char *target, char *content)
{
	new_envp->target = ft_strdup(target);
	if (new_envp->target == NULL)
	{
		free(new_envp);
		return (false);
	}
	if (content)
	{
		new_envp->value = ft_strdup(content);
		if (new_envp->value == NULL)
		{
			free_safely_str(new_envp->target);
			free(new_envp);
			return (false);
		}
		new_envp->value_size = ft_strlen(new_envp->value);
	}
	new_envp->target_size = ft_strlen(new_envp->target);
	return (true);
}

t_envp_list *create_new_envp(char *target, char *content)
{
	t_envp_list *new_envp;

	new_envp = allocate_envp_node();
	if (new_envp == NULL)
		return (NULL);
	if (!initialize_envp_node(new_envp, target, content))
	{
		free(new_envp);
		return (NULL);
	}
	return (new_envp);
}

int remove_env_var(t_envp_list **env, char *var)
{
	char	*tmp;
	t_envp_list *cpy;

	cpy = *env;
	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (MALLOC_FAILED);
	while (cpy)
	{
		if (ft_strncmp(tmp, cpy->target, ft_strlen(tmp)) == 0 || ft_strncmp(var, cpy->target, ft_strlen(var)) == 0)
		{
			remove_node_envp( env,cpy);
			break;
		}
		else
			cpy = cpy->next;
	}
	free_safely_str(tmp);
	return (0);
}

void remove_node_envp(t_envp_list **begin_list, t_envp_list *node_to_remove)
{
	t_envp_list *current;
	t_envp_list *previous_node;

	current = *begin_list;
	previous_node = NULL;
	while (current != NULL && current != node_to_remove)
	{
		previous_node = current;
		current = current->next;
	}
	if (current == node_to_remove)
	{
		if (previous_node != NULL)
			previous_node->next = current->next;
		else
			*begin_list = current->next;
		free_envp(current);
	}
}

void	free_envp(t_envp_list *envp)
{
	if (envp != NULL)
	{
		free_safely_str(envp->target);
		free_safely_str(envp->value);
		free(envp);
		envp = NULL;
	}
}
