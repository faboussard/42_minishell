/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mylib.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa  <faboussa@student.42lyon.f>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:23:45 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/22 17:07:06 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_putstr(char *s)
{
	if (s == NULL)
		return (write(1, "(null)", ft_strlen("(null)")));
	else
		return (write(1, s, ft_strlen(s)));
}

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}
