/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/22 10:58:07 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "lexer.h"

bool	define_builtin_token(t_token_list *new_token, const char *string,
		const char *builtins[8])
{
	int		i;
	size_t	len;

	len = ft_strlen(string) + 1;
	i = 0;
	while (i < 8)
	{
		if (builtins[i] != NULL && !ft_strncmp(string, builtins[i], len))
		{
			new_token->e_builtin = i;
			new_token->e_type = COMMAND;
			return (true);
		}
		i++;
	}
	return (false);
}

bool	get_builtin_token(t_token_list *new_token, char *string)
{
	const char	*builtins[8] = {[ECHO] = "echo", [CD] = "cd", [PWD] = "pwd",
			[EXIT] = "exit", [ENV] = "env", [EXPORT] = "export",
			[UNSET] = "unset"};

	return (define_builtin_token(new_token, string, builtins));
}

void	define_builtins(t_token_list *list_tokens)
{
	t_token_list	*iterator;

	iterator = list_tokens;
	while (iterator)
	{
		get_builtin_token(iterator, iterator->name);
		iterator = iterator->next;
	}
}