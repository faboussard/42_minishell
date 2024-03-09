/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/21 06:45:05 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*byte_dest;
	unsigned char	*byte_src;

	byte_dest = (unsigned char *)dest;
	byte_src = (unsigned char *)src;
	i = 0;
	if (dest == NULL && src == NULL)
		return (dest);
	while (i < n)
	{
		byte_dest[i] = byte_src[i];
		i++;
	}
	return (dest);
}
