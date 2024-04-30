/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "lexer.h"
#include "minishell.h"
#include "utils.h"
#include <readline/history.h>

//int	export(char **args, t_hashmap env_variables)
//{
//	size_t	index;
//
//	index = 1;
//	if (args[index] == NULL)
//	{
//		if (print_export(env_variables) < 0)
//		{
//			print_error("export", args[index], strerror(errno));
//			return (set_exit_code(1));
//		}
//	}
//	else
//		return (set_exit_code(export_variables(args + index, env_variables)));
//	return (set_exit_code(0));
//}
