/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/12/10 14:28:18 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include <stdlib.h>

static size_t	intlen(int n)
{
	size_t	i;

	i = 1;
	n /= 10;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*s;
	size_t		len;
	long int	nb;

	nb = n;
	len = intlen(n);
	if (n < 0)
	{
		nb = -nb;
		len++;
	}
	s = malloc(sizeof(char) * (len + 1));
	if (s == NULL)
		return (NULL);
	s[len] = '\0';
	while (len--)
	{
		s[len] = nb % 10 + '0';
		nb /= 10;
	}
	if (n < 0)
		s[0] = '-';
	return (s);
}
