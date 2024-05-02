/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:06:59 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/30 18:06:59 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <readline/history.h>


int ascending(char *a, char *b)
{
	return (ft_strcmp(a, b) <= 0);
}


t_envp_list *sort_envp_list(t_envp_list **lst, int (*cmp)(char *, char *))
{
	char *swap_target;
	char *swap_value;
	t_envp_list	*tmp;

	tmp = *lst;
	while((*lst)->next != NULL)
	{
		if (((*cmp)((*lst)->target, (*lst)->next->target)) == 0)
		{
			swap_value = (*lst)->value;
			swap_target = (*lst)->target;
			(*lst)->value = (*lst)->next->value;
			(*lst)->target = (*lst)->next->target;
			(*lst)->next->value = swap_value;
			(*lst)->next->target = swap_target;
		}
		else
			(*lst) = (*lst)->next;
	}
	(*lst) = tmp;
	return ((*lst));
}

void print_env_variables_export(t_minishell *m)
{
	t_envp_list	*current;
	char	*equal;

	current = m->list_envp;
	current = sort_envp_list(&current, ascending);
	while (current != NULL)
	{
		equal = ft_strchr(current->target, '=');
		if (equal == NULL)
			printf("declare -x %s\n", current->target - 1);
		else
			printf("declare -x %s\"%s\"\n", current->target, current->value);
		current = current->next;
	}
}
