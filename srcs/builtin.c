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

bool	get_builtin_token(t_token *new_token, char *string)
{
	int		i;
	const char *builtins[9] = {NULL,
	"echo", "cd", "ls", "pwd", "export", "unset", "env", "exit"
	};

	i = 1;
	while (i < 9)
	{
		if (!ft_strncmp(string, builtins[i], ft_strlen(string)))
		{
			define_token_types(COMMAND, i, NO_OPERATOR, new_token);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}