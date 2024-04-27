/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                               :+:      :+:    :+:   */
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

int ft_env(t_minishell *minishell, char **arg)
{
	if (arg && arg[1])
		print_error("minishell: exit: too many arguments");
	if (!minishell->list_envp)
		return (EXIT_FAILURE);
	print_list_envp(minishell);
	return (EXIT_SUCCESS);
}