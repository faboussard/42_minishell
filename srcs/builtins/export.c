/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/02 18:02:37 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "utils.h"
#include "parser.h"
#include <readline/history.h>

int make_export(char **args, t_envp_list *env_variables, t_minishell *m)
{
	size_t index;
	bool one_key_not_valid_return_1;

	one_key_not_valid_return_1 = false;
	index = 0;
	one_key_not_valid_return_1 = add_value_to_envp_list_if_valid(args, env_variables, m, index);
	if (one_key_not_valid_return_1 == true)
		return (1);
	else
		return (0);
}

char *find_and_join_value(const char *key, t_envp_list **head, char *value, t_minishell *m)
{
	char *new_value;
	t_envp_list *current;

	current = *head;
	new_value = NULL;
	while (current)
	{
		if (ft_strncmp(key, current->target, ft_strlen(key)) == 0)
		{
			if (!current->value)
			{
				new_value = ft_strdup(value);
				if (new_value)
					exit_msg(m, "Malloc failed at find_and_join_value", ENOMEM);
			}
			else
				new_value = join_with_old(head, value, m);
			break;
		}
		else
			current= current->next;
	}
	return (new_value);
}
