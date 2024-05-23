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
#include "builtins.h"
#include <readline/history.h>

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
			(*lst) = tmp;
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

	current = sort_envp_list(&m->list_envp, ascending);
	while (current != NULL)
	{
		equal = ft_strchr(current->target, '=');
		if (equal == NULL)
			printf("declare -x %s\n", current->target);
		else
			printf("declare -x %s\"%s\"\n", current->target, current->value);
		current = current->next;
	}
}

void	print_error_export(char *arg, bool *check_key)
{
	char *export_error;
	char *tmp;

	export_error = NULL;
	tmp = NULL;
	tmp = ft_strjoin("minishell: export: '", arg);
	if (!tmp)
	{
		ft_putstr_fd("Malloc failed at make_export\n", 2);
		return ;
	}
	export_error = ft_strjoin(tmp, "': not a valid identifier\n");
	if (!export_error)
	{
		free_safely_str(&tmp);
		ft_putstr_fd("Malloc failed at make_export\n", 2);
		return ;
	}
	ft_putstr_fd(export_error, 2);
	free_safely_str(&tmp);
	free_safely_str(&export_error);
	*check_key = true;
}