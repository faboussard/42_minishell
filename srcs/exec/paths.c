/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:51:27 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/03 11:54:44 by mbernard         ###   ########.fr       */
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
		malloc_error_with_exit(m);
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

static void	deal_with_pathed_cmd(t_minishell *m)
{
	m->pl->good_path = ft_strdup(m->pl->cmd_table[0]);
	if (m->pl->good_path == NULL)
		malloc_error_with_exit(m);
}

static void	check_path(t_minishell *m, t_process_list *pl, size_t i)
{
	char	*cmd_name;

	cmd_name = ft_strdup(pl->cmd_table[0]);
	if (!(pl->tab_paths[i]) && !ft_strncmp("/usr", m->paths, 5))
	{
		ft_free_tab(&(pl->tab_paths));
		free_safely_str(&(pl->good_path));
		free_safely_str(&(m->paths));
		print_name_and_exit_perror(m, cmd_name, 1);
	}
	else if (!(pl->tab_paths[i]))
	{
		free_safely_str(&(pl->good_path));
		ft_free_tab(&(pl->tab_paths));
		free_safely_str(&(m->paths));
		exit_command_not_found(m, cmd_name);
	}
	ft_free_tab(&(pl->tab_paths));
	free_safely_str(&cmd_name);
}

void	set_good_path_cmd(t_minishell *m, t_process_list *pl, char *cmd)
{
	size_t	i;

	if (((cmd[0] == '/' || cmd[0] == '.') || (ft_strchr(cmd, '/')))
		&& pl->cmd_table != NULL)
	{
		deal_with_pathed_cmd(m);
		return ;
	}
	pl->tab_paths = ft_split(m->paths, ':');
	if (pl->tab_paths == NULL || pl->cmd_table == NULL)
		malloc_error_with_exit(m);
	pl->good_path = join_sep(m, pl->tab_paths[0], pl->cmd_table[0], '/');
	if (pl->good_path == NULL)
		malloc_error_with_exit(m);
	i = 0;
	while (pl->tab_paths[i] && access(pl->good_path, F_OK) != 0)
	{
		free_safely_str(&(pl->good_path));
		pl->good_path = join_sep(m, pl->tab_paths[i], pl->cmd_table[0], '/');
		if (pl->good_path == NULL)
			malloc_error_with_exit(m);
		i++;
	}
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
		m->paths = ft_strdup("/usr");
	if (m->paths == NULL)
		malloc_error_no_exit(m);
}
/*
 *	No rights for non root users in /usr, they won't be able to place
 *	malicious software there.
 */
