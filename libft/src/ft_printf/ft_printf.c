/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa  <faboussa@student.42lyon.f>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 20:23:51 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/28 18:22:57 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static size_t	check_format(const char c, va_list args)
{
	int	out;

	out = 0;
	if (c == '\0')
		return (-1);
	if (c == '%')
		out = ft_putchar('%');
	if (c == 'c')
		out = ft_putchar(va_arg(args, int));
	else if (c == 'i' || c == 'd')
		out = ft_print_and_count_int(va_arg(args, int), BASE10);
	else if (c == 'p')
		out = print_and_count_ul(va_arg(args, unsigned long), BASE16_MIN);
	else if (c == 's')
		out = ft_putstr(va_arg(args, char *));
	else if (c == 'u')
		out = print_and_count_u(va_arg(args, unsigned int), BASE10);
	else if (c == 'x')
		out = print_and_count_u((va_arg(args, unsigned int)), BASE16_MIN);
	else if (c == 'X')
		out = print_and_count_u((va_arg(args, unsigned int)), BASE16_MAJ);
	return (out);
}

int	ft_printf(const char *s, ...)
{
	int		output;
	int		tmp;
	va_list	args;

	output = 0;
	va_start(args, s);
	while (*s != '\0')
	{
		tmp = output;
		if (*s == '%')
			output += check_format(*(++s), args);
		else
			output += ft_putchar(*s);
		if (output < tmp)
			return (-1);
		if (*s != '\0')
			s++;
	}
	return (va_end(args), output);
}
