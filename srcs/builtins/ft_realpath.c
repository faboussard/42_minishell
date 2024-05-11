/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:07:43 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/11 13:41:56 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"

/*
int	count_up_moves(char *cmd)
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
*/
/*
int	count_moves_to_root(char *cmd)
{
	int		moves;
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
}
*/

bool	begins_with_two_pts(const char *dir)
{
	size_t	i;

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
 */

void	remove_one_dir_from_path(char path[4096])
{
	size_t	path_len;
	size_t	i;

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

bool	next_dir_is_pts(const char *dir)
{
	size_t	i;

	i = 0;
	while (dir[i] && dir[i + 1])
	{
		if (dir[i] == '.' && dir[i + 1] == '.' && (!dir[i + 2] || dir[i + 2] == '/'))
			return (1);
		i++;
	}
	return (0);
}

size_t skip_slash_and_pts(const char *dir, size_t i)
{
	while (dir[i] && dir[i] == '/')
	{
		while (dir[i] && dir[i] == '/')
			i++;
		if (next_dir_is_pts(dir + i))
			i+= 2;
	}
	return (i);
}

void	replace_pts_with_path(t_minishell	*m, char target[4096], char	*dir)
{
	size_t i;
	size_t j;

	if (!dir || !dir[0])
		return ;
	i = 0;
	target[0] = '\0';
	i = skip_slash_and_pts(dir, i);
	while (dir[i])
	{
		while (dir[i] && dir[i - 1] != '/')
			i++;
		// FULL GARBAGE TO THINK ON
		while (next_dir_is_pts(dir + i))
		{
			j = i;
			while (dir[j] != '/')
				j--;
			ft_strlcat(target, dir, j + 1);
		}
		i++;
	}
}
/*
 *	remove_one_dir_from_path(m->target_path);
 * /../../../
 * /home/mbernard/42/minishell
 * 	size_t dir_len;
	size_t current_path_len;
	//dir_len = ft_strlen(dir);
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
*/

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
	replace_pts_with_path(m, m->target_path, dir);
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
