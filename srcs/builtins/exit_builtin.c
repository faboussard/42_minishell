/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "lexer.h"
#include "minishell.h"
#include "utils.h"
#include <readline/history.h>

static bool	check_out_of_range(int neg, unsigned long long num, bool *error)
{
	if ((neg == 1 && num > LONG_MAX) || (neg == -1 && num >
													  -(unsigned long)LONG_MIN))
		*error = true;
	return (*error);
}

static int	ft_atoi_long(const char *str, bool *error)
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
	while (str[i] && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		if (check_out_of_range(neg, num, error))
			break ;
		i++;
	}
	if (str[i] != '\0')
		*error = true;
	return (num * neg);
}


bool	str_is_num(char *str)
{
	int	x;

	x = 0;
	if (ft_strlen(str) == 1 && (str[x] < 0 || str[x] > 9))
		return (0);
	while (str[x])
	{
		if (ft_isalpha(str[x]))
			return (0);
		x++;
	}
	return (1);
}

int	ft_exit_builtin(t_minishell *minishell, char **cmd_table)
{
	int		exit_code;
	bool	error;

	error = false;
	printf("exit\n");
	if (!cmd_table[1])
	{
		free_minishell(minishell);
		exit(0);
	}
	exit_code = ft_atoi_long(cmd_table[1], &error);
	if (!str_is_num(cmd_table[1]))
		error = true;
	if (cmd_table[2] && !error)
	{
		print_error("minishell: exit: too many arguments");
		return (1);
	}
	else
	{
		if (error)
		{
			printf("minishell: exit: %s: numeric argument required",
				   cmd_table[1]);
			free_minishell(minishell);
			exit(2);
		}
		free_minishell(minishell);
		exit(exit_code % 256);
	}
}
