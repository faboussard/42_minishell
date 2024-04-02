/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdbool.h>
#include "minishell.h"

bool define_builtin_token(t_token *new_token, const char *string, const char *builtins[9])
{
	int i = 0;
	while (i < 9)
	{
		if (builtins[i] != NULL && !ft_strcmp(string, builtins[i]))
		{
			new_token->e_builtin = i;
			new_token->e_type = COMMAND;
			return true;
		}
		i++;
	}
	return false;
}

bool get_builtin_token(t_token *new_token, char *string)
{
	const char *builtins[9] = {
			[LS] = "ls",
			[ECHO] = "echo",
			[CD] = "cd",
			[PWD] = "pwd",
			[EXIT] = "exit",
			[ENV] = "env",
			[EXPORT] = "export",
			[UNSET] = "unset"
	};

	return define_builtin_token(new_token, string, builtins);
}
