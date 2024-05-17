/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 08:41:56 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/16 08:41:56 by mbernard         ###   ########.fr       */
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
		free(tmp->subdir);
		free(tmp);
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

t_dir_list 	*ft_split_list(char const *s, char c)
{
	t_dir_list	*list;
	t_dir_list 	*tmp;
	int		len_list;
	int		i;
	int		cursor;

	len_list = ft_len_list(s, c);
	list = (t_dir_list *)malloc(sizeof(t_dir_list) * (len_list + 1));
	if (!list)
		return (NULL);
	i = 0;
	cursor = 0;
	tmp = list;
	while (i < len_list)
	{
		tmp->subdir = ft_write_word((char *)s, c, &cursor);
		if (!list->subdir)
		{
			ft_free_list(list);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;
	return (list);
}