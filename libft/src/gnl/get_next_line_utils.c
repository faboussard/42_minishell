/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:02:50 by faboussa          #+#    #+#             */
/*   Updated: 2024/01/09 21:55:38 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr_gnl(char const *s, size_t total_len, unsigned int start,
		size_t len)
{
	char	*substr;
	size_t	i;
	char	*res;

	i = 0;
	if (start >= total_len)
	{
		res = malloc(1 * sizeof(char));
		if (res == NULL)
			return (NULL);
		return (res);
	}
	if (total_len <= start + len)
		substr = malloc(sizeof(char) * (total_len - start + 1));
	else
		substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (start < total_len && i < len)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}

int	ft_strchri(const char *s, size_t len, char c, size_t index)
{
	while (index < len - 1 && *(s + index) != c)
		index++;
	if (s[index] == c)
		return (index);
	return (-1);
}

char	*ft_concat(char *dst, const char *src, size_t src_len, size_t dstsize)
{
	unsigned long	dst_len;
	unsigned long	i;

	dst_len = ft_strlen(dst);
	i = 1;
	while (src_len + dst_len + 1 >= i * dstsize)
		i++;
	if (i != 1)
		dst = (char *)ft_realloc(dst, i * dstsize + 1);
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < src_len)
	{
		dst[dst_len] = src[i];
		dst_len++;
		i++;
	}
	dst[dst_len] = '\0';
	return (dst);
}
