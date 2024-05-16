/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 02:08:53 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/13 02:08:53 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_putendl_fd(const char *s, int fd)
{
	char *str;

	str = ft_strjoin(s, "\n");
	if (!str)
	{
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
	}
	else
	{
		write(fd, str, ft_strlen(str));
		free(str);
	}
}
