/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/09 18:12:22 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"

bool	is_valid_env_var_key(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (false);
	i++;
	while (var[i] != '\0')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	ft_unset(t_minishell *minishell, char **args)
{
	int	i;
	int	ret;

	i = 1;
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]))
		{
			print_cmd_perror_no_strerror(args[i], "unset: invalid parameter name");
			ret = EXIT_FAILURE;
		}
		else if (ft_strncmp(args[i], "_" , 2) != 0)
		{
			if (remove_env_var(&minishell->list_envp, args[i]) == MALLOC_FAILED)
				exit_msg(minishell, "Malloc failed at ft_unset", ENOMEM);
		}
		i++;
	}
	return (ret);
}
