/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/24 16:38:50 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"

int	ft_env(t_minishell *minishell, char **args)
{
	t_envp_list	*current;

	if (args && args[1])
	{
		print_error("env builtins: too many arguments");
		return (EXIT_FAILURE);
	}
	if (!minishell->list_envp)
		return (EXIT_FAILURE);
	current = minishell->list_envp;
	while (current != NULL)
	{
		if (ft_strchr(current->target, '='))
			printf("%s%s\n", current->target, current->value);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
