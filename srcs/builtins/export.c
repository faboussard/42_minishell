/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/24 15:50:26 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parser.h"
#include "utils.h"
#include <readline/history.h>

bool	is_valid_key_with_plus(char *key)
{
	size_t	index;

	index = 0;
	if (!ft_isalpha(key[index]) && key[index] != '_')
		return (false);
	while (key[index] != '\0')
	{
		if (key[index] == '+' && key[index + 1] == '\0')
			return (true);
		if (!ft_isalnum(key[index]) && key[index] != '_')
			return (false);
		index++;
	}
	return (true);
}

int	make_export(char **args, t_envp_list *env_variables, t_minishell *m)
{
	size_t	index;
	bool	one_key_not_valid_return_1;

	one_key_not_valid_return_1 = false;
	index = 0;
	one_key_not_valid_return_1 = add_value_to_envp_list_if_valid(args,
			env_variables, m, index);
	if (one_key_not_valid_return_1 == true)
		return (1);
	else
		return (0);
}

char	*find_and_join_value(const char *key, t_envp_list **head, char *value,
		t_minishell *m)
{
	char		*new_value;
	t_envp_list	*current;

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
			break ;
		}
		else
			current = current->next;
	}
	return (new_value);
}

char	*join_with_old(t_envp_list **list, char *content, t_minishell *m)
{
	char	*temp;
	char	*temp2;
	char	*new_content;

	temp = ft_strdup((*list)->value);
	if (temp == NULL)
		exit_msg(m, "Malloc failed at join_with_old", ENOMEM);
	temp2 = ft_strdup(content);
	if (temp2 == NULL)
	{
		free_safely_str(&temp);
		exit_msg(m, "Malloc failed at join_with_old", ENOMEM);
	}
	new_content = ft_strjoin(temp, temp2);
	free_safely_str(&temp);
	free_safely_str(&temp2);
	if (new_content == NULL)
		exit_msg(m, "Malloc failed at join_with_old", ENOMEM);
	return (new_content);
}

int	ascending(char *a, char *b)
{
	return (ft_strcmp(a, b) <= 0);
}
