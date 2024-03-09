/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/21 06:46:54 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*char_not_const;
	char	*last_occurrence;

	i = 0;
	last_occurrence = NULL;
	char_not_const = (char *)s;
	while (char_not_const[i] != '\0')
	{
		if (char_not_const[i] == (char)c)
			last_occurrence = char_not_const;
		char_not_const++;
	}
	if (*char_not_const == (char)c)
		return (char_not_const);
	return (last_occurrence);
}
