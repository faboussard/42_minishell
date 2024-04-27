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
	while (str[x])
	{
		if (ft_isalpha(str[x]))
			return (1);
		x++;
	}
	return (0);
}

int	ft_exit_builtin(t_minishell *minishell, char **cmd_table)
{
	int		exit_code;
	bool	is_alpha;

	is_alpha = false;
	printf("exit\n");
	if (!cmd_table[1])
	{
		free_minishell(minishell);
		exit(0);
	}
	exit_code = ft_atoi_long(cmd_table[1], &is_alpha);
	if (!str_is_num(cmd_table[1]))
		is_alpha = true;
	if (cmd_table[2] && !is_alpha)
	{
		print_error("minishell: exit: too many arguments");
		return (1);
	}
	else
	{
		if (is_alpha)
		{
			printf("minishell: exit: %s: numeric argument required\n",
				   cmd_table[1]);
			free_minishell(minishell);
			exit(2);
		}
		free_minishell(minishell);
		exit(exit_code % 256);
	}
}
