/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:07:43 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/22 08:44:37 by mbernard         ###   ########.fr       */
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

bool	invalid_num_of_pts(char *cmd)
{
	size_t	i;

	i = 0;
	if (!cmd)
		return (0);
	if (!ft_strchr(cmd, '.'))
		return (0);
	while (cmd[i] && cmd[i + 1] && cmd[i + 2])
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

void	ft_realpath(t_minishell *m, char *cmd)
{
	int		up_moves;
	int		moves_to_root;
	size_t	future_path_len;

	if (!cmd || !cmd[0] || !cmd[1] || invalid_num_of_pts(cmd)
		|| !contains_only_charset(cmd, "./"))
	{
		ft_strlcpy(m->target_path, cmd, ft_strlen(cmd) + 1);
		return ;
	}
	up_moves = count_up_moves(cmd);
	moves_to_root = count_moves_to_root(m->current_path);
	if (up_moves >= moves_to_root)
		ft_strlcpy(m->target_path, "/", 2);
	else
	{
		future_path_len = count_future_path_len(m->current_path, up_moves);
		ft_strlcpy(m->target_path, m->current_path, future_path_len);
	}
	return ;
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
	while (target[i] && i < PATH_MAX)
	{
		target[i] = '\0';
		i++;
	}
	++(*j);
	dprintf(2, "target after final slash = %s\n", target);
//	target[*j] = '/';
//	target[*j] = '\0';
}

void sanitize_path(char path[PATH_MAX], size_t end)
{
	size_t	i;
	size_t	j;
	char tmp[4096];

	i = 0;
	j = 0;
	clear_path_char(tmp);
	dprintf(2, "tmp = %s\n", tmp);
	dprintf(2, "path = %s\n", path);
	ft_memset(path + end, 0, PATH_MAX - end);
//	path[end] = '\0';
	while (path[i])
	{
		if (path[i] == '/' && path[i + 1] && path[i + 1] == '/')
			i++;
		else
		{
			tmp[j] = path[i];
			dprintf(2, "tmp = %s\n", tmp);
			i++;
			j++;
		}
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
//	char	tmp[PATH_MAX];
	char cp_dir[ARG_MAX];

	if (!dir || !dir[0])
		return ;
	ft_strlcpy(cp_dir, dir, ARG_MAX);
	i = 0;
	j = ft_strlen(m->current_path);
//	tmp[0] = '\0';
	ft_strlcpy(target, m->current_path, j + 1);
	up_moves = count_up_moves(cp_dir);
	if (up_moves >= count_moves_to_root(m->current_path))
	{
		ft_strlcpy(target, "/", 2);
		return ;
	}
	dprintf(2, "CURRENT PATH = %s\n", m->current_path);
	dprintf(2, "dir = %s\n", cp_dir);
	if (cp_dir[0] && cp_dir[0]!= '/')
		target[j++] = '/';
	sanitize_path(target, j); // J aurais essaye !!!!!
	while (cp_dir[i])
	{
		if (next_dir_is_pts(cp_dir + i))
			go_back_dir(target, &i, &j);
		if (cp_dir[i] == '/' || cp_dir[i] == '\0')
			put_final_slash(target, &j);
		else
		{
			target[j] = cp_dir[i];
			j++;
		}
		i++;
	}
	target[j] = '\0';
	dprintf(2, "TARGET = %s\n", target);
}

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
			sanitize_path(m->target_path, ft_strlen(m->target_path));
			return ;
		}
	replace_pts_with_path(m, m->target_path, dir);
	dprintf(2, "I BUG :D\n%s\n", m->target_path);
	sanitize_path(m->target_path, ft_strlen(m->target_path));
}

/*
a/b/c/d/e/f/g/h/i
a/b/c/../c/../../b/

a
b
NULL
*/