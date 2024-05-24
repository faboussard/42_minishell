/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:31:01 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/24 20:31:01 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"

bool	is_one_arg_builtin(t_minishell *m)
{
	if (m->total_commands == 1)
	{
		if (m->list_tokens->e_builtin == EXIT)
			return (1);
		if (m->list_tokens->e_builtin == UNSET)
			return (1);
		if (m->list_tokens->e_builtin == CD)
			return (1);
		if (m->list_tokens->e_builtin == EXPORT)
			return (1);
	}
	return (0);
}

bool	exec_builtin(t_minishell *m, char *cmd, char **cmd_table)
{
	if (!cmd || !cmd_table)
		return (0);
	if (cmd && ft_strncmp(cmd, "echo", 5) == 0)
		m->status = ft_echo(cmd_table);
	else if (cmd && ft_strncmp(cmd, "cd", 3) == 0)
		m->status = ft_cd(m, cmd_table);
	else if (cmd && ft_strncmp(cmd, "pwd", 4) == 0)
		m->status = ft_pwd(m);
	else if (cmd && ft_strncmp(cmd, "exit", 5) == 0)
		m->status = ft_exit(m, cmd_table);
	else if (cmd && ft_strncmp(cmd, "env", 4) == 0)
		m->status = ft_env(m, cmd_table);
	else if (cmd && ft_strncmp(cmd, "unset", 6) == 0)
		m->status = ft_unset(m, cmd_table);
	else if (cmd && ft_strncmp(cmd, "export", 7) == 0)
		m->status = ft_export(cmd_table, &m->list_envp, m);
	else
		return (0);
	set_or_get_last_status(m->status, 0);
	return (1);
}

bool	is_builtin(char *cmd, char **cmd_table)
{
	if (!cmd || !cmd_table)
		return (0);
	if (cmd && ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	else if (cmd && ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	else if (cmd && ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (cmd && ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	else if (cmd && ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	else if (cmd && ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	else if (cmd && ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	else
		return (0);
}
