/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/05 11:19:07 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "utils.h"
#include <stdbool.h>

bool	define_builtin_token(t_token_list *new_token, const char *string,
		const char *builtins[8])
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (builtins[i] != NULL && !ft_strcmp(string, builtins[i]))
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
