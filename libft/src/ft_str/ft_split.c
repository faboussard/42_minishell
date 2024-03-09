/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 21:04:58 by faboussa          #+#    #+#             */
/*   Updated: 2023/12/10 16:43:33 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static void	*ft_free_all_alloc(char **strs_array, size_t start)
{
	size_t	i;

	i = 0;
	while (i < start)
	{
		free(strs_array[i]);
		i++;
	}
	free(strs_array);
	return (NULL);
}

static size_t	count_letters(const char *str, char c)
{
	size_t	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str != c)
			count++;
		str++;
	}
	return (count);
}

static char	**fill_array_with_strings(char **strs_array, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			len = 0;
			while (s[i + len] && s[i + len] != c)
				len++;
			strs_array[j] = ft_substr(s, i, len);
			if (strs_array[j] == NULL)
				return (ft_free_all_alloc(strs_array, j));
			j++;
			i += len;
		}
		else
			i++;
	}
	strs_array[j] = NULL;
	return (strs_array);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (s == NULL)
		return (NULL);
	split = malloc(sizeof(char **) * (count_letters(s, c) + 1));
	if (split == NULL)
		return (NULL);
	split = fill_array_with_strings(split, s, c);
	if (split == NULL)
	{
		free(split);
		return (NULL);
	}
	return (split);
}
