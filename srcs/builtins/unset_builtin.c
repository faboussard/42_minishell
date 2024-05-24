/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/24 16:27:34 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
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

void	print_error_unset(char *arg)
{
	char	*unset_error;
	char	*tmp;

	unset_error = NULL;
	tmp = NULL;
	tmp = ft_strjoin("unset: ", arg);
	if (!tmp)
	{
		ft_putstr_fd("Malloc failed at print_error_export\n", 2);
		return ;
	}
	unset_error = ft_strjoin(tmp, ": invalid parameter name\n");
	if (!unset_error)
	{
		free_safely_str(&tmp);
		ft_putstr_fd("Malloc failed at print_error_export\n", 2);
		return ;
	}
	ft_putstr_fd(unset_error, 2);
	free_safely_str(&tmp);
	free_safely_str(&unset_error);
}

int	ft_unset(t_minishell *minishell, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]))
			print_error_unset(args[i]);
		else if (ft_strncmp(args[i], "_", 2) != 0)
		{
			if (remove_env_var(&minishell->list_envp, args[i]) == MALLOC_FAILED)
				exit_msg_minishell(minishell, "Malloc failed at ft_unset",
					ENOMEM);
		}
		i++;
	}
	return (0);
}
