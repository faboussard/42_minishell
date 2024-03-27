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

#define NOT_FOUND 1
#define MALLOC_FAILED -1
#define SUCCESSFULLY_ADDED 0

//content doit etre pouvoir nul ?
static int	add_new_envp(t_node **list_envp, char *target, char *content)
{
	t_envp_content		*new_node_content;
	t_node				*new_node;

	new_node_content = malloc(sizeof(t_envp_content));
	if (new_node_content == NULL)
		return (MALLOC_FAILED);
	new_node_content->target = ft_strdup(target);
	if (new_node_content->target == NULL)
	{
		free(new_node_content);
		return (MALLOC_FAILED);
	}
	if (content)
	{
		new_node_content->value = ft_strdup(content);
		if (new_node_content->value == NULL)
		{
			free(new_node_content->target);
			free(new_node_content);
			return (MALLOC_FAILED);
		}
		new_node_content->value_size = ft_strlen(new_node_content->value);
	}
	new_node_content->target_size = ft_strlen(new_node_content->target);
	new_node = ft_lstnew(new_node_content);
	if (new_node == NULL)
	{
		free_t_envp_content(new_node_content);
		return (MALLOC_FAILED);
	}
	ft_lstadd_front(list_envp, new_node);
	return (SUCCESSFULLY_ADDED);
}

int get_target_and_value(char **envp, t_node **list_envp, t_minishell *minishell)
{
	size_t	i;
	char	*content;
	char	*target;

	i = 0;
	while ((*envp)[i] && (*envp)[i] != '=')
		i++;
	target = ft_substr(*envp, 0, i + 1);
	if (target == NULL)
	{
		ft_lstclear(list_envp, (void *) free_t_envp_content);
		return (0);
	}
	if ((*envp)[i] == '=')
	{
		i++;
		content = ft_substr(*envp, i, ft_strlen(*envp) - i);
		if (add_new_envp(list_envp, target, content) == MALLOC_FAILED)
		{
			ft_lstclear(list_envp, (void *) free_t_envp_content);
			return (0);
		}
		minishell->total_size_envp += ft_strlen(target) + ft_strlen(content);
        if (content != NULL)
            free(content);
	}
	free(target);
	return (1);
}

int create_dict_env_variable(char **envp, t_node **list_envp, t_minishell *minishell)
{
	while (*envp && ft_strchr(*envp, '='))
	{
		if (!get_target_and_value(envp, list_envp, minishell))
			return (0);
		envp++;
	}
	return (1);
}

t_node *create_envp_list(char **envp, t_minishell *minishell)
{
	t_node *list_envp;

	list_envp = NULL;
	if (!create_dict_env_variable(envp, &list_envp, minishell))
		return (NULL);
	return (list_envp);
}
