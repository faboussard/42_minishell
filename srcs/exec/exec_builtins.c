/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/11 10:23:46 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "utils.h"
#include "builtins.h"

void restore_terminal(t_minishell *minishell)
{
	dprintf(2, "I'm about to free !");
	free_minishell(minishell);
}

int exec_builtin(t_minishell *minishell, t_token_list *command)
{
	if (command->e_builtin == CD)
		return (ft_cd(minishell, command));
	if (command->e_builtin == EXIT)
		return (ft_exit_builtin(minishell, command));
	return (0);
}