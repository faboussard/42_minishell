/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:03:42 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/25 17:50:30 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	deal_with_pathed_cmd(t_pipex *p)
{
	p->good_path = ft_strdup(p->cmd_args[0]);
	if (p->good_path == NULL)
		exit_msg_pipex(p, "Malloc error", -1);
}

static void	deal_with_quotations_marks(char *joined_cmd)
{
	size_t	x;
	bool	end_of_arg;

	x = 0;
	end_of_arg = 0;
	while (joined_cmd[x])
	{
		if (joined_cmd[x] == '\'' && joined_cmd[x - 1] == '\"' && !end_of_arg)
			break ;
		if (joined_cmd[x] == '\'' && (joined_cmd[x - 1] != '\"' || end_of_arg))
		{
			joined_cmd[x] = '\"';
			end_of_arg = 1;
		}
		x++;
	}
}

static void	set_cmd_with_apostrophes(t_pipex *p, char *cmd)
{
	char	*begin;
	char	*joined_cmd;
	size_t	x;

	x = 0;
	while (cmd[x] && cmd[x] != ' ')
		x++;
	x++;
	begin = malloc(sizeof(char) * x);
	if (!begin)
		exit_msg_pipex(p, "Malloc error", -1);
	ft_strlcpy(begin, cmd, x);
	joined_cmd = ft_strjoin(begin, cmd + x);
	free(begin);
	if (!joined_cmd)
		exit_msg_pipex(p, "Malloc error", -1);
	deal_with_quotations_marks(joined_cmd);
	p->cmd_args = ft_split(joined_cmd, '\"');
	free(joined_cmd);
	if (!p->cmd_args)
		exit_msg_pipex(p, "Malloc error", -1);
}

void	set_cmd_args(t_pipex *p, char *cmd)
{
	size_t	x;

	x = 0;
	while (cmd[x] && cmd[x] != '\'' && cmd[x] != '\"')
		x++;
	if (!cmd[x])
	{
		p->cmd_args = ft_split(cmd, ' ');
		if (!p->cmd_args)
			exit_msg_pipex(p, "Malloc error", -1);
	}
	else
		set_cmd_with_apostrophes(p, cmd);
}

void	set_good_path_with_cmd(t_pipex *p, char *cmd)
{
	size_t	x;

	set_cmd_args(p, cmd);
	if (((cmd[0] == '/' || cmd[0] == '.') || (ft_strchr(cmd, '/')))
		&& p->cmd_args != NULL)
	{
		deal_with_pathed_cmd(p);
		return ;
	}
	p->tab_paths = ft_split(p->paths, ':');
	if (p->tab_paths == NULL || p->cmd_args == NULL)
		exit_msg_pipex(p, "Malloc error", -1);
	p->good_path = join_sep(p, p->tab_paths[0], p->cmd_args[0], '/');
	x = 0;
	while (p->tab_paths[x] && access(p->good_path, F_OK) != 0)
	{
		free(p->good_path);
		p->good_path = join_sep(p, p->tab_paths[x], p->cmd_args[0], '/');
		x++;
	}
	if (!(p->tab_paths[x]) && !ft_strncmp("N", p->paths, 2))
		print_name_and_exit_perror(p, p->cmd_args[0], 1);
	else if (!(p->tab_paths[x]))
		exit_command_not_found(p, p->cmd_args[0]);
}
