/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 02:16:38 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/22 12:27:24 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*str;
	char		*c2;

	str = s1;
	if (s1 == NULL || set == NULL)
		return (ft_strdup(s1));
	while (ft_strchr(set, *str) && *str)
		str++;
	c2 = ft_strchr(str, '\0');
	while (str < c2 && ft_strchr(set, *(c2 - 1)))
		c2--;
	return (ft_substr(str, 0, c2 - str));
}
