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

#include <stdlib.h>
#include "lexer.h"
#include "utils.h"
#include "minishell.h"
#include "parser.h"

void add_envp_to_list(t_envp_list **list_envp, t_envp_list *new_envp)
{
	if (new_envp == NULL)
		return;
	new_envp->next = *list_envp;
	*list_envp = new_envp;
}

static int add_new_envp(t_envp_list **list_envp, char *target, char *content)
{
    t_envp_list *new_envp;

    new_envp = create_new_envp(target, content);
    if (new_envp == NULL)
        return (MALLOC_FAILED);
    add_envp_to_list(list_envp, new_envp);
    return (SUCCESSFULLY_ADDED);
}

int get_target_and_value(char **envp, t_envp_list **list_envp, t_minishell *minishell)
{
    size_t  i;
    char    *content;
    char    *target;

    i = 0;
    while ((*envp)[i] && (*envp)[i] != '=')
        i++;
    target = ft_substr(*envp, 0, i + 1);
    if (target == NULL)
        exit_msg(minishell, "Malloc failed at get_target_and_value", 2);
    if ((*envp)[i] == '=')
    {
        i++;
        content = ft_substr(*envp, i, ft_strlen(*envp) - i);
        if (content == NULL)
			exit_msg(minishell, "Malloc failed at get_target_and_value", 2);
        if (add_new_envp(list_envp, target, content) == MALLOC_FAILED)
            return (0);
		minishell->total_size_envp += ft_strlen(target) + ft_strlen(content);
		free_safely_str(content);
	}
	free_safely_str(target);
	return (1);
}

int create_env_variable(char **envp, t_envp_list **list_envp, t_minishell *minishell)
{
	while (*envp && ft_strchr(*envp, '='))
	{
		if (!get_target_and_value(envp, list_envp, minishell))
			return (0);
		envp++;
	}
	return (1);
}

t_envp_list *create_envp_list(char **envp, t_minishell *minishell)
{
    t_envp_list *list_envp;

	list_envp = NULL;
	if (!create_env_variable(envp, &list_envp, minishell))
		return (NULL);
	return (list_envp);
}
