/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa  <faboussa@student.42lyon.f>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:55:25 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/28 13:15:06 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	print_and_count_ul(unsigned long int n, char *base)
{
	unsigned long int	size;
	int					result;

	result = 0;
	if (n == 0)
		return (ft_putstr("(nil)"));
	else
	{
		size = ft_strlen(base);
		if (n >= size)
		{
			result += print_and_count_ul(n / size, base);
			if (result == -1)
				return (-1);
			return (ft_putchar(base[n % size]) + result);
		}
		else
			return (ft_putstr("0x") + ft_putchar(base[n % size]));
	}
}

int	print_and_count_u(unsigned int n, char *base)
{
	unsigned int	size;
	int				result;

	result = 0;
	size = ft_strlen(base);
	if (n >= size)
	{
		result += print_and_count_u(n / size, base);
		if (result == -1)
			return (-1);
		return (ft_putchar(base[n % size]) + result);
	}
	else
		return (ft_putchar(base[n % size]));
}

int	ft_print_and_count_int(int n, const char *base)
{
	int	size;
	int	result;

	result = 0;
	size = ft_strlen(base);
	if (n == 0)
		return (ft_putchar('0'));
	if (n == INT_MIN)
		return (ft_putstr("-2147483648"));
	else if (n < 0 && n != INT_MIN)
	{
		if (ft_putchar('-') == -1)
			return (-1);
		result++;
		n = -n;
	}
	if (n < size && n > 0)
		return (ft_putchar(base[n % size]) + result);
	else if (n >= size)
	{
		result += ft_print_and_count_int(n / size, base);
		if (result == -1)
			return (-1);
	}
	return (ft_putchar(base[n % size]) + result);
}
