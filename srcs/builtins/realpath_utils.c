/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realpath_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:07:43 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/18 22:55:22 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_realpath.h"

size_t	count_up_moves(char *cmd)
{
	size_t	up_moves;
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
	size_t	moves;
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
	return (0);
}

void	remove_node_from_list(t_dir_list *node)
{
	t_dir_list	*prev;
	t_dir_list	*next;

	if (!node)
		return ;
	prev = node->prev;
	next = node->next;
	if (prev)
		prev->next = next;
	else if (next)
		next->prev = NULL;
	if (next)
		next->prev = prev;
	else if (prev)
		prev->next = NULL;
	free_safely_str(&node->subdir);
	free(node);
	node = NULL;
}

char	*join_sep_safely(char *s1, char *s2, char sep, bool free_s1)
{
	size_t	total_len;
	char	*dest;
	int		x;
	int		y;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	dest = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!dest)
		return (NULL);
	x = -1;
	y = 0;
	while (s1[++x])
		dest[x] = (char)s1[x];
	if (sep)
		dest[x++] = sep;
	while (s2[y])
		dest[x++] = (char)s2[y++];
	dest[x] = '\0';
	if (free_s1)
		free_safely_str(&s1);
	return (dest);
}
