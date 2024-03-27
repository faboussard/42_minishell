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

#include "lexer.h"
#include "minishell.h"
#include "utils.h"
#include "parser.h"
#include "signals.h"
# include <readline/history.h>

//The exit utility shall cause the shell to exit from its current
//execution environment with the exit status specified by the
//unsigned decimal integer n.  If the current execution environment
//        is a subshell environment, the shell shall exit from the subshell
//        environment with the specified exit status and continue in the
//environment from which that subshell environment was invoked;
//otherwise, the shell utility shall terminate with the specified
//exit status. If n is specified, but its value is not between 0
//and 255 inclusively, the exit status is undefined.
//
//A trap on EXIT shall be executed before the shell terminates,
//except when the exit utility is invoked in that trap itself, in
//        which case the shell shall exit immediately.

void restore_terminal(t_minishell *minishell)
{
	free_minishell(minishell);
}

int ft_exit(t_minishell *minishell)
{
    if (!minishell->list_tokens->next)
	{
		restore_terminal(minishell);
		exit(0);
	}
	else
		exit(1);
}