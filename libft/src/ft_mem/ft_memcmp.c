/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/11 08:46:22 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_memcmp(void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*byte_s1;
	unsigned char	*byte_s2;

	i = 0;
	byte_s1 = (unsigned char *)s1;
	byte_s2 = (unsigned char *)s2;
	while (i < n)
	{
		if (byte_s1[i] != byte_s2[i])
			return (byte_s1[i] - byte_s2[i]);
		i++;
	}
	return (0);
}
