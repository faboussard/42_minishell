/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/27 09:31:09 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"
#include <stdlib.h>

char	*extract_target(char **envp, size_t i, t_minishell *m)
{
	char	*target;

	target = ft_substr(*envp, 0, i + 1);
	if (target == NULL)
		exit_msg(m, "Malloc failed at extract_target", ENOMEM);
	return (target);
}

char	*free_safely_content(t_minishell *m, const char *content, char **target)
{
	if (content == NULL)
	{
		free_safely_str(target);
		exit_msg(m, "Malloc failed at get_target", ENOMEM);
	}
	return (*target);
}

void	get_target_and_value(char **envp, t_envp_list **l_envp, t_minishell *m)
{
	size_t	i;
	char	*content;
	char	*target;

	i = 0;
	while ((*envp)[i] && (*envp)[i] != '=')
		i++;
	target = extract_target(envp, i, m);
	if ((*envp)[i] == '=')
	{
		i++;
		content = ft_substr(*envp, i, ft_strlen(*envp) - i);
		target = free_safely_content(m, content, &target);
		if (add_new_envp(l_envp, target, content) == MALLOC_FAILED)
		{
			free_all(target, content);
			exit_msg(m, "Malloc failed at get_target", ENOMEM);
		}
		m->total_size_envp += ft_strlen(target) + ft_strlen(content);
		free_safely_str(&content);
	}
	free_safely_str(&target);
}

void	create_env_variable(char **envp, t_envp_list **list_envp,
		t_minishell *m)
{
	while (*envp && ft_strchr(*envp, '='))
	{
		get_target_and_value(envp, list_envp, m);
		envp++;
	}
}

t_envp_list	*create_envp_list(char **envp, t_minishell *minishell)
{
	t_envp_list	*list_envp;

	list_envp = NULL;
	create_env_variable(envp, &list_envp, minishell);
	if (list_envp != NULL)
		assign_shell_and_shell_level(&list_envp, minishell);
	return (list_envp);
}
