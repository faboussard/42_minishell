/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:07:43 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/12 20:08:30 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"

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

size_t	count_moves_to_root(char *cmd)
{
	size_t		moves;
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

/*
 * static void	remove_one_dir_from_path(char path[4096])
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
 *
 */

static bool	begins_with_two_pts(const char *dir)
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

static bool	invalid_num_of_pts(char *dir)
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

static bool	next_dir_is_pts(const char *dir)
{
	if (dir[0] && dir[1])
	{
		if (dir[0] == '.' && dir[1] == '.' && (!dir[2] || dir[2] == '/'))
			return (1);
	}
	return (0);
}

//static size_t	count_up_moves(const char *dir, size_t i)
//{
//	size_t up_moves;
//
//	up_moves = 0;
//	if (next_dir_is_pts(dir + i))
//	{
//		up_moves++;
//		i += 2;
//	}
//	while (dir[i] && dir[i] == '/')
//	{
//		while (dir[i] && dir[i] == '/')
//			i++;
//		if (next_dir_is_pts(dir + i))
//		{
//			up_moves++;
//			i += 2;
//		}
//	}
//	return (up_moves);
//}

void	go_back_dir(const char *target, size_t *i, size_t *j)
{
	if ((*j) > 0)
	{
		(*j)--;
		while ((*j) > 0 && target[(*j) - 1] != '/')
			(*j)--;
	}
	(*i) += 2;
}

void put_final_slash(char *target, size_t *j)
{
	size_t i;

	dprintf(2, "target BEFORE final slash = %s\n", target);
	if (!target[(*j)] || *j == 0 || target[(*j) - 1] != '/')
	{
		target[*j] = '/';
		(*j)++;
	}
	i = *j;
	while (target[i])
	{
		target[i] = '\0';
		i++;
	}
	dprintf(2, "target after final slash = %s\n", target);
//	target[*j] = '/';
//	++(*j);
//	target[*j] = '\0';
}

void sanitize_path(char path[PATH_MAX])
{
	size_t	i;
	size_t	j;
	char tmp[4096];

	i = 0;
	j = 0;
	clear_path_char(tmp);
	while (path[i])
	{
		if (path[i] == '/' && path[i + 1] && path[i + 1] == '/')
			i++;
		else
			tmp[j] = path[i];
		i++;
		j++;
	}
	tmp[j] = 0;//'\0';
	dprintf(2, "tmp = %s\n", tmp);
	ft_strlcpy(path, tmp, j + 1);
}

void	replace_pts_with_path(t_minishell	*m, char target[PATH_MAX], char	*dir)
{
	size_t	i;
	size_t	j;
	size_t up_moves;
	char	tmp[PATH_MAX];

	if (!dir || !dir[0])
		return ;
	i = 0;
	j = ft_strlen(m->current_path);
	tmp[0] = '\0';
	ft_strlcpy(target, m->current_path, j + 1);
	up_moves = count_up_moves(dir);
	if (up_moves >= count_moves_to_root(m->current_path))
	{
		ft_strlcpy(target, "/", 2);
		return ;
	}
	dprintf(2, "CURRENT PATH = %s\n", m->current_path);
	if (dir[0] && dir[0]!= '/')
		target[j++] = '/';
	sanitize_path(target); // J aurais essaye !!!!!
	while (dir[i])
	{
		if (next_dir_is_pts(dir + i))
			go_back_dir(target, &i, &j);
		//sanitize_path(target); // J aurais essaye !!!!!
		if (dir[i] == '/' || dir[i] == '\0')
			put_final_slash(target, &j);
		else
		{
			target[j] = dir[i];
			j++;
		}
		i++;
	}
	target[j] = '\0';
}
/*
void	replace_pts_with_path(t_minishell	*m, char target[4096], char	*dir)
{
	size_t	i;
	size_t	j;
	char	tmp[4096];

	(void)m;
	if (!dir || !dir[0])
		return ;
	i = 0;
	tmp[0] = '\0';
	target[0] = '\0';
	i = skip_slash_and_pts(dir, i);
	while (dir[i])
	{
		while (i > 1 && dir[i] && dir[i - 1] != '/')
			i++;
		// FULL GARBAGE TO THINK ON
		while (dir[i] && next_dir_is_pts(dir + i))
		{
			j = i - 1;
			while (dir[j] != '/')
				j--;
			ft_strlcat(tmp, dir, j + 1);
			ft_strlcat(target, tmp, j + 1);
			i += 2;
		}
		i++;
	}
}
*/
/*
 *	remove_one_dir_from_path(m->target_path);
 *	/../home/../home/mbernard/42/minishell
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
	size_t	dir_len;
	size_t	curpath_len;
	char tmp[PATH_MAX];

	clear_path_char(tmp);
	dir_len = ft_strlen(dir);
	ft_strlcpy(m->target_given, dir, dir_len + 1);
	if (ft_strncmp(dir, "/", 2) == 0)
	{
		ft_strlcpy(m->target_path, dir, 2);
		return ;
	}
	if (dir && dir[0] == '/')
		return ;
	if ((dir_len <= PATH_MAX
		&& ((ft_strchr(dir, '.') == NULL) || !ft_strncmp(dir, ".", 2))
		&& (!dir[0] || !dir[1] || invalid_num_of_pts(dir))))
	//	|| access(m->current_path, X_OK) == 0))
		{
//			dprintf(2, "dir = %s\n", dir);
			curpath_len = ft_strlen(m->current_path);
			ft_strlcpy(tmp, m->current_path, curpath_len + 1);
			ft_strlcat(tmp, "/", curpath_len + 2);
			ft_strlcat(tmp, dir, curpath_len + 2 + dir_len);
			ft_strlcpy(m->target_path, tmp, ft_strlen(tmp) + 1);
			sanitize_path(m->target_path);
			return ;
		}
	replace_pts_with_path(m, m->target_path, dir);
	sanitize_path(m->target_path);
}
/*
a/b/c/d/e/f/g/h/i
a/b/c/../c/../../b/

a
b
NULL
*/
