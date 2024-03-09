/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/21 06:46:47 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*little_found;

	little_found = (char *)big;
	i = 0;
	if (little[0] == '\0')
		return (&little_found[i]);
	while (big[i] != '\0')
	{
		j = 0;
		while (big[i + j] == little[j] && ((i + j) < len))
		{
			if (big[i + j] == '\0' && little[j] == '\0')
				return (&little_found[i]);
			j++;
		}
		if (little[j] == '\0')
			return (little_found + i);
		i++;
	}
	return (0);
}
