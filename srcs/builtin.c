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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "../libft/inc/libft.h"
#include "error.h"

int is_builtin(char *command_name)
{
	if (ft_strcmp(command_name, "echo") == 0)
		return (ECHO);
	if (ft_strcmp(command_name, "cd") == 0)
		return (CD);
	if (ft_strcmp(command_name, "ls") == 0)
		return (LS);
	if (ft_strcmp(command_name, "pwd") == 0)
		return (PWD);
	if (ft_strcmp(command_name, "export") == 0)
		return (EXPORT);
	if (ft_strcmp(command_name, "unset") == 0)
		return (UNSET);
	if (ft_strcmp(command_name, "env") == 0)
		return (ENV);
	if (ft_strcmp(command_name, "exit") == 0)
		return (EXIT);
	else
		return (-1);
}

bool	create_builtin_token(t_token *new_token, char *string)
{
	int		i;
	int 	built_n;

	i = 0;
	while (i < BUILTINS_COUNT)
	{
		built_n = is_builtin(string);
		if (is_builtin(string) !=  -1)
		{
			define_token(COMMAND, built_n, NO_OPERATOR, new_token);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}