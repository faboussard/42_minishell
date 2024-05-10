/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:07:43 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/11 00:24:34 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"

/*int	count_up_moves(char *cmd)
{
	int		up_moves;
	size_t	i;

	up_moves = 0;
	i = 0;
	if (!cmd)
		return (0);
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
	size_t	i;

	moves = 0;
	i = 0;
	if (!cmd)
		return (0);
	while (cmd[i])
	{
		if (cmd[i] == '/')
			moves++;
		i++;
	}
	return (moves);
}*/
bool	begins_with_two_pts(char *dir)
{
	i = 0;
	while (dir[i] && dir[i + 1])
	{
		if (dir[i] != '.' || dir[i + 1] != '/')
			break ;
		i += 2;
	}
	if (dir[i] && dir[i + 1] && (!dir[i + 2] || dir[i + 2] == '/'))
	{
		if (dir[i] == '.' && dir[i + 1] == '.')
			return (1);
	}
	return (0);
}

bool	invalid_num_of_pts(char *dir)
{
	size_t	i;

	i = 0;
	if (!dir)
		return (0);
	if (!ft_strchr(dir, '.'))
		return (0);
	while (dir[i] && dir[i + 1] && dir[i + 2])
	{
		if (dir[i] == '.' && dir[i + 1] == '.' && dir[i + 2] == '.')
			return (1);
		i++;
	}
	if (begins_with_two_pts(dir))
		return (0);
	return (1);
}

/*
 * size_t	count_future_path_len(char *current_path, int up_moves)
{
	size_t	i;
	int		slash_seen;
	int		total_slash;
	size_t	i;
	size_t	path_len;

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
}*/
void	remove_one_dir_from_path(char path[4096])
{
	path_len = ft_strlen(path);
	if (path_len < 3)
	{
		ft_strlcpy(path, "/", 2);
		return ;
	}
	i = path_len - 2;
	while (path[i] != '/' && i > 0)
		i--;
	if (i == 0 || i > path_len)
		ft_strlcpy(path, "/", 2);
	else
	{
		while (path[i])
		{
			path[i] = '\0';
			i++;
		}
	}
}

void	normalize_path(char *path)
{
	char	*src;
	char	*dst;
	size_t	i;

	src = path;
	dst = path;
	i = 0;
	while (src[i])
	{
		if (src[i] == '/')
		{
			/* Skip multiple / */
			while (src[i + 1] && src[i + 1] == '/')
				i++;
			/* Skip . */
			if (src[i + 1) == '.' && (!src[i + 2] || src[i = 2] == '/'))
			{
				i += 2;
				continue ;
			}
			/* Skip .. and back up one level */
			if (src[i = 1] == '.' && src[i + 2] == '.' && (!src[i + 3]
					|| src [i + 3] == '/'))
			{
				i += 3;
				while (dst > path && *--dst != '/')
					;
				continue ;
			}
			/* Check for ... and return an error */
			if (*(src + 1) == '.' && *(src + 2) == '.' && *(src + 3) == '.'
				&& (*(src + 4) == '/' || *(src + 4) == '\0'))
			{
				fprintf(stderr, "Error: Invalid path\n");
				return ;
			}
		}
		/* Copy next path segment */
		while (*src && *src != '/')
			*dst++ = *src++;
	}
	/* Null terminate the normalized path */
	*dst = '\0';
}

/*void	replace_pts_with_path(t_minishell	*m, char	*dir)
{
	size_t	i;
	size_t	j;
	size_t	dir_len;
	size_t	current_path_len;

	i = 0;
	j = 0;
	dir_len = ft_strlen(dir);
	current_path_len = ft_strlen(m->current_path);
	ft_strlcat(m->target_path, dir, dir_len + 1);
	while (dir[i] && dir[i + 1])
	{
		if (dir[i] == '.' && dir[i + 1] == '/')
			i += 2;
		else if (dir[i] == '.' && dir[i + 1] == '.' && dir[i + 2] == '/')
		{
			remove_one_dir_from_path(new_path);
			i += 3;
		}
		else
		{
			new_path[current_path_len + j] = dir[i];
			i++;
			j++;
		}
	}
	new_path[current_path_len + j] = '\0';
	ft_strlcpy(current_path, new_path, ft_strlen(new_path) + 1);
}*/
void	ft_realpath(t_minishell *m, char *dir)
{
	//	size_t	future_path_len;
	ft_strlcpy(m->target_given, dir, ft_strlen(dir) + 1);
	if (!dir || !dir[0] || !dir[1] || invalid_num_of_pts(dir)
		|| access(m->current_path, X_OK) == 0)
	{
		ft_strlcpy(m->target_path, dir, ft_strlen(dir) + 1);
		return ;
	}
	normalize_path(dir);
	//	ft_strlcpy(m->target_path, m->current_path, ft_strlen(m->current_path));
	//	remove_one_dir_from_path(m->target_path);
	//	if (dir[2] == '/')
	//	{
	//		future_path_len = ft_strlen(m->target_path) + ft_strlen(&dir[2])
				+ 1;
	//		ft_strlcat(m->target_path, &dir[2], future_path_len);
	//	}
}
/*
 * Si access
	dprintf(2, "target_path: %s\n", m->target_path);
 *
 * 	//int		up_moves;
	//int		moves_to_root;
 * up_moves = count_up_moves(cmd);
moves_to_root = count_moves_to_root(m->current_path);
if (up_moves >= moves_to_root)
	ft_strlcpy(m->target_path, "/", 2);
else
{
	future_path_len = count_future_path_len(m->current_path, up_moves);
	ft_strlcpy(m->target_path, m->current_path, future_path_len);
}
 */
/*
a/b/c/d/e/f/g/h/i
a/b/c/../c/../../b/

a
b
NULL
*/
