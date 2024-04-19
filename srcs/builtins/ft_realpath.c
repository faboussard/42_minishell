/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:07:43 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/19 12:18:30 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"
#include "utils.h"

int	count_up_moves(char *cmd)
{
	int		up_moves;
	size_t	i;

	up_moves = 0;
	i = 0;
	while (cmd && cmd[i] && cmd[i + 1])
	{
		if (cmd[i] == '.' && cmd[i + 1] == '.')
			up_moves++;
		i++;
	}
	return (up_moves);
}

int	count_moves_to_root(char *cmd)
{
	int		moves;
	size_t	i;

	moves = 0;
	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '/')
			moves++;
		i++;
	}
	return (moves);
}

bool	invalid_num_of_pts(char *cmd)
{
	size_t	i;

	i = 0;
	if (cmd)
	{
		if (!ft_strchr(cmd, '.'))
			return (0);
	}
	while (cmd && cmd[i] && cmd[i + 1] && cmd[i + 2])
	{
		if (cmd[i] == '.' && cmd[i + 1] == '.' && cmd[i + 2] == '.')
			return (1);
		i++;
	}
	return (0);
}

size_t	count_future_path_len(char *current_path, int up_moves)
{
	size_t	i;
	int		slash_seen;
	int		total_slash;

	i = 0;
	slash_seen = 0;
	total_slash = 0;
	while (current_path[i])
	{
		if (current_path[i] == '/')
			total_slash++;
		i++;
	}
	i = 0;
	while (current_path[i] && slash_seen <= total_slash - up_moves)
	{
		if (current_path[i] == '/')
			slash_seen++;
		i++;
	}
	i++;
	return (i);
}

char	*ft_realpath(t_minishell *m, char *cmd)
{
	char	*realpath;
	int		up_moves;
	int		moves_to_root;
	size_t	future_path_len;

	if (!cmd || !cmd[0] || !cmd[1] || invalid_num_of_pts(cmd)
		|| !contains_only_charset(cmd, "./"))
		return (NULL);
	up_moves = count_up_moves(cmd);
	moves_to_root = count_moves_to_root(m->current_path);
	if (up_moves >= moves_to_root)
		realpath = ft_strdup("/");
	else
	{
		future_path_len = count_future_path_len(m->current_path, up_moves);
		realpath = ft_calloc(future_path_len, sizeof(char));
		if (realpath != NULL)
			ft_strlcpy(realpath, m->current_path, future_path_len);
	}
	if (realpath == NULL)
	{
		malloc_error_no_exit(m);
		return (NULL);
	}
	m->target_path = realpath;
	dprintf(2, "current path was %s\n", m->current_path);
	dprintf(2, "going into %s with a len of %lu\n", realpath, future_path_len);
	return (realpath);
}
/*
a/b/c/d/e/f/g/h/i
a/b/c/../c/../../b/

a
b
NULL
*/