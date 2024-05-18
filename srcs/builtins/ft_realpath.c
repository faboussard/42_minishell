/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:07:43 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/17 23:06:47 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_realpath.h"

void	remove_dirs_from_list(t_dir_list **list)
{
	t_dir_list	*tmp;
	t_dir_list	*start;

	tmp = *list;
	while (tmp && ft_strncmp(tmp->subdir, "..", 3) == 0)
		remove_node_from_list(tmp);
	start = tmp;
	while (tmp)
	{
		if (tmp->next && ft_strncmp(tmp->next->subdir, "..", 3) == 0)
		{
			remove_node_from_list(tmp->next);
			remove_node_from_list(tmp);
			tmp = start;
		}
		else if (ft_strncmp(tmp->subdir, ".", 2) == 0
			|| ft_strncmp(tmp->subdir, "..", 3) == 0)
		{
			remove_node_from_list(tmp);
			tmp = start;
		}
		tmp = tmp->next;
	}
	tmp = NULL;
	*list = start;
}

bool	add_root_node(t_dir_list **list)
{
	(*list)->prev = (t_dir_list *) malloc(sizeof(t_dir_list));
	if (!(*list)->prev)
	{
		ft_free_list(*list);
		return (0);
	}
	(*list)->prev->next = *list;
	*list = (*list)->prev;
	(*list)->subdir = ft_strdup("/");
	if (!*list || !(*list)->subdir)
	{
		ft_free_list(*list);
		return (0);
	}
	return (1);
}

t_dir_list	*prepare_list(t_minishell *m, char *dir)
{
	t_dir_list	*list;
	char		*dir_cpy;

	dir_cpy = ft_strdup(dir);
	if (!dir_cpy)
		return (NULL);
	if (dir && dir[0] && dir[0] != '/')
	{
		free_safely_str(&dir_cpy);
		dir_cpy = join_sep_safely(m->current_path, dir, '/', 0);
		if (!dir_cpy)
			return (NULL);
	}
	list = ft_split_list(dir_cpy, '/');
	free_safely_str(&dir_cpy);
	if (!list)
		return (NULL);
	if (add_root_node(&list) == 0)
		return (NULL);
	return (list);
}

char	*replace_pts_with_path(t_minishell	*m, char *dir)
{
	char		*path;
	t_dir_list	*list;
	t_dir_list	*start;

	list = prepare_list(m, dir);
	if (!list)
		return (NULL);
	remove_dirs_from_list(&list);
	if (!list || !list->next)
		return (ft_strdup("/"));
	path = ft_strdup(list->subdir);
	if (!path)
	{
		ft_free_list(list);
		return (NULL);
	}
	start = list;
	while (list->next)
	{
		list = list->next;
		if (ft_strncmp(path, "/", 2) == 0)
			path = ft_strjoin(path, list->subdir);
		else
			path = join_sep_safely(path, list->subdir, '/', 1);
		if (!path)
			break ;
	}
	list = start;
	ft_free_list(list);
	return (path);
}

char	*ft_realpath(t_minishell *m, char *dir)
{
	if (ft_strncmp(dir, "/", 2) == 0)
		return (ft_strdup("/"));
	if ((dir && dir[0] == '/' && ft_strchr(dir, '.') == NULL)
		|| invalid_num_of_pts(dir))
		return (ft_strdup(dir));
	if (contains_only_charset(dir, "./")
		&& count_moves_to_root(m->current_path) < count_up_moves(dir))
		return (ft_strdup("/"));
	return (replace_pts_with_path(m, dir));
}
