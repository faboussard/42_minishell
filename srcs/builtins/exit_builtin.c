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
#include "utils.h"

//bool str_is_num(char *str)
//{
//	int i;
//
//	i = 0;
//	while (str[i])
//	{
//		if (ft_isalpha(str[i]))
//			return (1);
//		i++;
//	}
//	return (0);
//}

bool str_is_not_num(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i])
			|| (!ft_isdigit(str[i]) && i == 0 && str[i] != '-' && str[i] != '+')
			|| ((str[0] == '-' || str[0] == '+') && !str[1]))
			return (1);
		i++;
	}
	return (0);
}


void exit_numeric_arg(t_minishell *minishell, char *const *cmd_table, bool is_alpha)
{
	if (is_alpha)
	{
		print_cmd_perror_no_strerror(cmd_table[1], "exit: numeric argument required\n");
		free_minishell(minishell);
		exit(2);
	}
}

void exit_no_arg(t_minishell *minishell, char *const *cmd_table)
{
	if (!cmd_table[1])
	{
		free_minishell(minishell);
		exit(0);
	}
}

int	ft_exit(t_minishell *minishell, char **cmd_table)
{
	int	exit_code;
	bool	is_alpha;

	is_alpha = false;
	if (minishell->interactive)
		ft_putendl_fd("exit", 2);
	exit_no_arg(minishell, cmd_table);
	exit_code = ft_atoi_long(cmd_table[1], &is_alpha);
	if (str_is_not_num(cmd_table[1]))
		is_alpha = true;
	if (cmd_table[2] && !is_alpha)
	{
		print_error("minishell: exit: too many arguments");
		minishell->status = set_or_get_last_status(1, 0);
		return (1);
	}
	exit_numeric_arg(minishell, cmd_table, is_alpha);
	free_minishell(minishell);
	exit(exit_code % 256);
}
