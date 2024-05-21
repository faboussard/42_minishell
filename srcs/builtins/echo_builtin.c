/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/21 10:35:06 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_n_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **cmd_table)
{
	bool	flag;
	size_t	i;

	i = 1;
	flag = 0;
	while (cmd_table[i] && check_n_arg(cmd_table[i]))
	{
		flag = 1;
		i++;
	}
	while (cmd_table[i])
	{
		if (cmd_table[i] && printf("%s", cmd_table[i]) == -1)
			return (EXIT_FAILURE);
		i++;
		if (cmd_table[i] && printf(" ") == -1)
			return (EXIT_FAILURE);
	}
	if (flag == 0 && printf("\n") == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
