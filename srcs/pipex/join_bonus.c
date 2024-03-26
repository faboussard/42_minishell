/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:35:38 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/20 18:12:01 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*join_sep(t_pipex *p, char *s1, char *s2, char sep)
{
	size_t	total_len;
	char	*dest;
	int		x;
	int		y;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	dest = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!dest)
		exit_msg_pipex(p, "Malloc error", -1);
	x = -1;
	y = 0;
	while (s1[++x])
		dest[x] = (char)s1[x];
	dest[x++] = sep;
	while (s2[y])
		dest[x++] = (char)s2[y++];
	dest[x] = '\0';
	return (dest);
}
