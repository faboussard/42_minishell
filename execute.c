/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c             			                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/22 12:10:15 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "utils.h"
#include "builtins.h"


int exec_builtin(t_minishell *minishell, t_token *command)
{
	if (command->e_builtin == EXIT)
		return (ft_exit_builtin(minishell));
	return (0);
}

void execute(t_minishell *minishell)
{
	t_token *token;

	token = (t_token *)(minishell->list_tokens)->content;
	if (token->e_builtin != 0)
		exec_builtin(minishell, token);
	//else
		//exec_external(minishell);
}
