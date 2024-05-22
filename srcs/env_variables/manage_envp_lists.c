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

t_envp_list *allocate_envp_node(void)
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

bool init_envp_node(t_envp_list *new_envp, char *target, char *content)
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

t_envp_list *create_new_envp(char *target, char *content)
{
	t_envp_list *new_envp;

	new_envp = allocate_envp_node();
	if (new_envp == NULL)
		return (NULL);
	if (!init_envp_node(new_envp, target, content))
	{
		free(new_envp);
		return (NULL);
	}
	return (new_envp);
}

char *trim_equal_sign(char *key)
{
	char *trimmed_key;

	trimmed_key = ft_strtrim(key, "=");
	if (trimmed_key == NULL)
		return (NULL);
	return (trimmed_key);
}

int iterate_and_remove_node(t_envp_list **env, char *key)
{
	char *target_without_equal_sign;
	t_envp_list *cpy;
	size_t len;

	len = ft_strlen(key) + 1;
	cpy = *env;
	while (cpy)
	{
		target_without_equal_sign = trim_equal_sign(cpy->target);
		if (target_without_equal_sign == NULL)
		{
			free_safely_str(&key);
			return (MALLOC_FAILED);
		}
		if (ft_strncmp(key, target_without_equal_sign, len) == 0)
		{
			remove_node_envp(env, cpy);
			free_safely_str(&target_without_equal_sign);
			break;
		}
		else
			cpy = cpy->next;
		free_safely_str(&target_without_equal_sign);
	}
	return (0);
}

int remove_env_var(t_envp_list **env, char *key)
{
	char *key_without_equal_sign;

	key_without_equal_sign = NULL;
	if (ft_strchr(key, '='))
	{
		key_without_equal_sign = trim_equal_sign(key);
		if (key_without_equal_sign == NULL)
			return (MALLOC_FAILED);
	}
	if (key_without_equal_sign)
	{
		if (iterate_and_remove_node(env, key_without_equal_sign) == MALLOC_FAILED)
		{
			free_safely_str(&key_without_equal_sign);
			return (MALLOC_FAILED);
		}
	}
	else
	{
		if (iterate_and_remove_node(env, key) == MALLOC_FAILED)
		return (MALLOC_FAILED);
	}
	free_safely_str(&key_without_equal_sign);
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

void free_envp(t_envp_list *envp)
{
	if (envp != NULL)
	{
		free_safely_str(&(envp->target));
		free_safely_str(&(envp->value));
		free(envp);
		envp = NULL;
	}
}
