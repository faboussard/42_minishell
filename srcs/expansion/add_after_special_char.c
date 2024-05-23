/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/11 17:01:49 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int is_special_char(char c)
{
	if (c == '$' || c == '`' || c == '=')
		return (1);
	return (0);
}

int check_special_char_after_expand(char *string, char *string2)
{
	int i;
	int j;

	i = 0;
	j = ft_strlen(string2);
	while (string[i] && string[i] != is_special_char(string2[j - 1]))
		i++;
	if (string[i] == string2[j])
		return (1);
	return (0);
}