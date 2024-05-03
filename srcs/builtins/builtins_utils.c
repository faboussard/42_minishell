/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 08:17:34 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/19 12:05:30 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

bool	contains_only_charset(const char *str, const char *charset)
{
	while (*str != '\0')
	{
		if (ft_strchr(charset, *str) == NULL)
			return (0);
		str++;
	}
	return (1);
}

bool is_valid_key_with_plus(char *key)
{
	size_t index;

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

void join_equal_sign(char **split)
{
	char *tmp;

	tmp = ft_strdup(split[0]);
	free(split[0]);
	split[0] = ft_strjoin(tmp, "=");
	free(tmp);
}

void join_with_old(t_minishell *m, char **split, t_envp_list **cpy, char *temp)
{
	temp = join_new_value_env_with_old(m, split, cpy);
	free(split[1]);
	split[1] = ft_strdup(temp);
	free(temp);
}

void action_for_no_valid_key(char *arg, bool *check_key)
{
	print_cmd_perror_no_strerror(arg, "export: invalid identifier\n");
	*check_key = true;
}