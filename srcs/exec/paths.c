/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:51:27 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/16 08:54:57 by mbernard         ###   ########.fr       */
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
	i = 0;
	while (pl->tab_paths[i] && access(pl->good_path, F_OK) != 0)
	{
		free(pl->good_path);
		pl->good_path = join_sep(m, pl->tab_paths[i], pl->cmd_table[0], '/');
		i++;
	}
	if (!(pl->tab_paths[i]) && !ft_strncmp("/usr", m->paths, 2))
		print_name_and_exit_perror(m, pl->cmd_table[0], 1);
	else if (!(pl->tab_paths[i]))
		exit_command_not_found(m, pl->cmd_table[0]);
}

static bool	this_is_path(char *var)
{
	if (!var)
		return (0);
	if (!var[0] || var[0] != 'P')
		return (0);
	if (!var[1] || var[1] != 'A')
		return (0);
	if (!var[2] || var[2] != 'T')
		return (0);
	if (!var[3] || var[3] != 'H')
		return (0);
	if (!var[4] || var[4] != '=')
		return (0);
	return (1);
}

void	set_paths(t_minishell *m, char **env)
{
	size_t	i;

	i = 0;
	while (env && env[i])
	{
		if (this_is_path(env[i]))
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
