/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:03:42 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/25 16:38:28 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	set_paths(t_pipex *p, char **env)
{
	size_t	x;

	x = 0;
	while (env && env[x])
	{
		if (this_is_path(env[x]))
		{
			p->paths = ft_strdup(env[x] + 5);
			if (p->paths == NULL)
				exit_msg_pipex(p, "Malloc error", -1);
			break ;
		}
		x++;
	}
	if (p->paths == NULL)
		p->paths = ft_strdup("N");
	if (p->paths == NULL)
		exit_msg_pipex(p, "Malloc error", -1);
}
