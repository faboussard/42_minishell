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

#include "lexer.h"
#include "minishell.h"
#include "utils.h"
#include "builtins.h"

//The exit utility shall cause the shell to exit from its current
//execution environment with the exit status specified by the
//unsigned decimal integer n.  If the current execution environment
//        is a subshell environment, the shell shall exit from the subshell
//        environment with the specified exit status and continue in the
//environment from which that subshell environment was invoked;
//otherwise, the shell utility shall terminate with the specified
//exit status. If n is specified, but its value is not between 0
//and 255 inclusively, the exit status is undefined.
//
//A trap on EXIT shall be executed before the shell terminates,
//except when the exit utility is invoked in that trap itself, in
//        which case the shell shall exit immediately.

//FAIRE EXIT QUAND ON FAIT CONTRLOLE D AUSSI ( pour linstant seul un % apparait)

static int	get_exit_code(char *arg, bool *error);
static bool	check_out_of_range(int neg, unsigned long long num, bool *error);

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

static bool	check_out_of_range(int neg, unsigned long long num, bool *error)
{
	if ((neg == 1 && num > LONG_MAX)
		|| (neg == -1 && num > -(unsigned long)LONG_MIN))
		*error = true;
	return (*error);
}

int ft_exit_builtin(t_minishell *minishell, t_token_list *command)
{
	int		exit_code;
	bool	error;
	error = false;

	printf("exit\n");
	if (!command->next)
	{
		restore_terminal(minishell);
		exit(0);
	}
	exit_code = ft_atoi_long(command->next->name, &error);
	if (command->next->next && !error)
	{
		print_error("minishell: exit: too many arguments");
		minishell->status = 127;
		//verifier le numero dexit . retourne 1 ou bien 127 ???
		return (1);
	}
	else
	{
		if (error)
		{
			printf("minishell: exit: %s: numeric argument required",	command->next->name);
			restore_terminal(minishell);
			exit(2);
		}
		exit(exit_code % 256);
	}
}