/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_envp_lists.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:37:43 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/09 22:08:51 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include <string.h>

//<<<<<<< HEAD
//    new_envp = malloc(sizeof(t_envp_list));
//    if (new_envp == NULL)
//        return (NULL);
//    new_envp->target = ft_strdup(target);
//    if (new_envp->target == NULL) {
//        free(new_envp);
//        return (NULL);
//    }
//    if (content)
//	{
//        new_envp->value = ft_strdup(content);
//        if (new_envp->value == NULL)
//		{
//			free_safely_str(&(new_envp->target));
//            free(new_envp);
//            return (NULL);
//        }
//        new_envp->value_size = ft_strlen(new_envp->value);
//    }
//    new_envp->target_size = ft_strlen(new_envp->target);
//    return (new_envp);
//=======
t_envp_list	*allocate_envp_node(void)
{
	t_envp_list	*new_envp;

	new_envp = ft_calloc(1, sizeof(t_envp_list));
	if (new_envp == NULL)
		return (NULL);
	new_envp->target = NULL;
	new_envp->value = NULL;
	new_envp->target_size = 0;
	new_envp->value_size = 0;
	return (new_envp);
}

bool	initialize_envp_node(t_envp_list *new_envp, char *target, char *content)
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
			free_safely_str(&new_envp->target);
			free(new_envp);
			return (false);
		}
		new_envp->value_size = ft_strlen(new_envp->value);
	}
	new_envp->target_size = ft_strlen(new_envp->target);
	return (true);
}

t_envp_list	*create_new_envp(char *target, char *content)
{
	t_envp_list	*new_envp;

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

int	remove_env_var(t_envp_list **env, char *var)
{
	char		*target_without_equal_sign;
	t_envp_list	*cpy;

	cpy = *env;
	while (cpy)
	{
		target_without_equal_sign = ft_strtrim(cpy->target, "=");
		if (target_without_equal_sign == NULL)
			return (MALLOC_FAILED);
		if (ft_strncmp(var, target_without_equal_sign, ft_strlen(var)) == 0
			|| ft_strncmp(var, target_without_equal_sign, ft_strlen(var)) == 0)
		{
			remove_node_envp(env, cpy);
			free_safely_str(&target_without_equal_sign);
			break ;
		}
		else
			cpy = cpy->next;
		free_safely_str(&target_without_equal_sign);
	}
	return (0);
}

void	remove_node_envp(t_envp_list **begin_list, t_envp_list *node_to_remove)
{
	t_envp_list	*current;
	t_envp_list	*previous_node;

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
		free_safely_str(&(envp->target));
		free_safely_str(&(envp->value));
		free(envp);
		envp = NULL;
	}
}
