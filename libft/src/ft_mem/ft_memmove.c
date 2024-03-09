/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/21 06:45:17 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_byte;
	unsigned char	*src_byte;

	if (dest == NULL && src == NULL)
		return (dest);
	dest_byte = (unsigned char *)dest;
	src_byte = (unsigned char *)src;
	if (dest_byte < src_byte)
		ft_memcpy(dest, src, n);
	else
	{
		while (n > 0)
		{
			dest_byte[n - 1] = src_byte[n - 1];
			n--;
		}
	}
	return (dest);
}
