/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:51:27 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/24 19:55:34 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*join_sep(t_minishell *m, char *s1, char *s2, char sep)
{
	size_t	total_len;
	char	*dest;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	dest = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!dest)
		exit_msg_minishell(m, "Malloc error in paths", ENOMEM);
	i = -1;
	j = 0;
	while (s1[++i])
		dest[i] = (char)s1[i];
	dest[i++] = sep;
	while (s2[j])
		dest[i++] = (char)s2[j++];
	dest[i] = '\0';
	return (dest);
}

static void	check_path(t_minishell *m, t_process_list *pl, size_t i)
{
	char	*cmd_name;

	cmd_name = ft_strdup(pl->cmd_table[0]);
	if (!(pl->tab_paths[i]) && !ft_strncmp("/no_path_set", m->paths, 13))
	{
		ft_free_tab(&(pl->tab_paths));
		free_safely_str(&(pl->good_path));
		free_safely_str(&(m->paths));
		print_name_and_exit_perror(m, cmd_name, 127);
	}
	else if (!(pl->tab_paths[i]))
		exit_command_not_found(m, cmd_name, pl, 1);
	ft_free_tab(&(pl->tab_paths));
	free_safely_str(&cmd_name);
}

static size_t	search_the_right_path(t_minishell *m, t_process_list *pl)
{
	size_t	i;

	i = 0;
	while (pl->tab_paths[i] && access(pl->good_path, F_OK) != 0)
	{
		free_safely_str(&(pl->good_path));
		pl->good_path = join_sep(m, pl->tab_paths[i], pl->cmd_table[0], '/');
		if (pl->good_path == NULL)
			exit_msg_minishell(m, "Malloc error in paths", ENOMEM);
		if (access(pl->good_path, F_OK) == 0)
			break ;
		i++;
	}
	return (i);
}

void	set_good_path_cmd(t_minishell *m, t_process_list *pl, char *cmd)
{
	size_t	i;

	if (((cmd[0] == '/' || cmd[0] == '.') || (ft_strchr(cmd, '/')))
		&& pl->cmd_table != NULL)
	{
		m->pl->good_path = ft_strdup(m->pl->cmd_table[0]);
		if (m->pl->good_path == NULL)
			exit_msg_minishell(m, "Malloc error in paths", ENOMEM);
		return ;
	}
	pl->tab_paths = ft_split(m->paths, ':');
	if (pl->tab_paths == NULL || pl->cmd_table == NULL)
		exit_msg_minishell(m, "Malloc error in paths", ENOMEM);
	pl->good_path = join_sep(m, pl->tab_paths[0], pl->cmd_table[0], '/');
	if (pl->good_path == NULL)
		exit_msg_minishell(m, "Malloc error in paths", ENOMEM);
	i = search_the_right_path(m, pl);
	check_path(m, pl, i);
}

void	set_paths(t_minishell *m, char **env)
{
	size_t	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			m->paths = ft_strdup(env[i] + 5);
			if (m->paths == NULL)
			{
				malloc_error_no_exit(m);
				return ;
			}
			break ;
		}
		i++;
	}
	if (m->paths == NULL)
		m->paths = ft_strdup("/no_path_set");
	if (m->paths == NULL)
		malloc_error_no_exit(m);
}
