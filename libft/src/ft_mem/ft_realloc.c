/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:16:37 by faboussa          #+#    #+#             */
/*   Updated: 2024/02/15 12:16:43 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_realloc(void *ptr, unsigned int new_size)
{
	char			*new;
	char			*temp;
	unsigned int	i;

	if (ptr == NULL)
	{
		ptr = malloc(new_size);
		return (ptr);
	}
	if (new_size == 0)
		return (free(ptr), NULL);
	new = malloc(new_size + 1);
	if (new == NULL)
		return (NULL);
	temp = ptr;
	i = 0;
	while (i < new_size && temp[i] != '\0')
	{
		new[i] = temp[i];
		i++;
	}
	new[i] = '\0';
	free(ptr);
	return (new);
}
