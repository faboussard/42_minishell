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
#include "general.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "../libft/inc/libft.h"
#include "error.h"

void cpy_string_builtin(char builtins[7][10])
{
	ft_strcpy(builtins[LS], "ls");
	ft_strcpy(builtins[ECHO], "echo");
	ft_strcpy(builtins[CD], "cd");
	ft_strcpy(builtins[PWD], "pwd");
	ft_strcpy(builtins[EXIT], "exit");
	ft_strcpy(builtins[ENV], "env");
	ft_strcpy(builtins[EXPORT], "export");
	ft_strcpy(builtins[UNSET], "unset");
}

bool	define_builtin(t_token *new_token, char *string)
{
	int		i;
	char	builtins[8][10];

	cpy_string_builtin(builtins);
	i = 0;
	while (i < 8)
	{
		if (!ft_strncmp(string, builtins[i], ft_strlen(string)))
		{
			define_token(COMMAND, i, NO_OPERATOR, new_token);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}