/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 08:41:56 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/18 14:04:40 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_realpath.h"

static int	ft_len_list(char const *s, char c)
{
	int	len_list;
	int	check;

	len_list = 0;
	check = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			if (check == 0)
				len_list++;
			check = 1;
		}
		else if (*s == c)
			check = 0;
		s++;
	}
	return (len_list);
}

void	ft_free_list(t_dir_list *list)
{
	t_dir_list	*tmp;

	if (!list)
		return ;
	while (list)
	{
		tmp = list;
		list = list->next;
		free_safely_str(&tmp->subdir);
		free(tmp);
		bzero(tmp, sizeof(t_dir_list));
	}
	list = NULL;
}

static char	*ft_write_word(char *s, char c, int *cursor)
{
	int		len;
	char	*word;

	len = 0;
	while (s[*cursor] == c)
		(*cursor)++;
	while (s[len + *cursor] && s[len + *cursor] != c)
		len++;
	word = ft_substr(s, *cursor, len);
	*cursor += len;
	return (word);
}

bool	assign_node(t_dir_list **list, char const *s, char c, int *cursor)
{
	(*list)->subdir = ft_write_word((char *)s, c, cursor);
	if (!(*list)->subdir)
	{
		ft_free_list(*list);
		return (1);
	}
	(*list)->next = (t_dir_list *)malloc(sizeof(t_dir_list));
	if (!(*list)->next)
	{
		ft_free_list(*list);
		return (1);
	}
	(*list)->next->prev = *list;
	*list = (*list)->next;
	return (0);
}

t_dir_list	*ft_split_list(char const *s, char c)
{
	t_dir_list	*list;
	t_dir_list	*start;
	int			len_list;
	int			cursor;

	len_list = ft_len_list(s, c);
	list = (t_dir_list *)malloc(sizeof(t_dir_list) * (len_list + 1));
	if (!list)
		return (NULL);
	ft_bzero(list, sizeof(t_dir_list));
	cursor = 0;
	start = list;
	while (len_list-- > 0)
	{
		if (assign_node(&list, s, c, &cursor))
			return (NULL);
	}
	if (list->prev != NULL)
		list->prev->next = NULL;
	ft_bzero(list, sizeof(t_dir_list));
	free(list);
	list = NULL;
	list = start;
	return (list);
}
