/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/22 12:10:15 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	writenumber(int n)
{
	if (n > 9)
		writenumber(n / 10);
	write(1, &"0123456789"[n % 10], 1);
}

void	fizzbuzz(void)
{
	int	n;

	n = 1;
	while (n <= 100)
	{
		if (n % 3 == 0 && n % 5 == 0)
			write(1, "fizzbuzz", 9);
		else if (n % 3 == 0)
			write(1, "fizz", 5);
		else if (n % 5 == 0)
			write(1, "buzz", 5);
		else
			writenumber(n);
		write(1, "\n", 1);
		n++;
	}
}

int	main(void)
{
	fizzbuzz();
	return (0);
}
