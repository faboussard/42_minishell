/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:52:07 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/21 15:56:02 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	check_out_of_range(int neg, unsigned long long num, bool *error)
{
	if ((neg == 1 && num > LONG_MAX)
		|| (neg == -1 && num > -(unsigned long)LONG_MIN))
		*error = true;
	return (*error);
}

int	check_by_digit(const char *str, bool *error, int neg,
		unsigned long long int *num)
{
	int	i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		*num = (*num * 10) + (str[i] - '0');
		if (check_out_of_range(neg, *num, error))
			break ;
		i++;
	}
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

int	ft_atoi_long(const char *str, bool *error)
{
	unsigned long long	num;
	int					neg;
	int					i;

	num = 0;
	neg = 1;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	i += check_by_digit(str + i, error, neg, &num);
	if (str[i] != '\0')
		*error = true;
	return (num * neg);
}
