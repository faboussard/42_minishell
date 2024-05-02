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

void print_env_variables_export(t_envp_list **envp)
{
	t_envp_list	*current;
	char	*equal;

	current = *envp;
	while (current != NULL)
	{
		equal = ft_strchr(current->target, '=');
		if (equal == NULL)
			ft_printf("declare -x %s\n", current->target - 1);
		else
		{
			*equal = '\0';
			ft_printf("declare -x %s=\"%s\"\n", current->target, current->value);
		}
		current = current->next;
	}
}
