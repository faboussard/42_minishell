/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:06:59 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/30 18:06:59 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parser.h"
#include "minishell.h"
#include "utils.h"
#include <readline/history.h>

//static int	print_env_variables_export(char **envp)
//{
//	char	*equal;
//	size_t	index;
//
//	index = 0;
//	while (envp[index] != NULL)
//	{
//		equal = ft_strchr(envp[index], '=');
//		if (equal == NULL)
//			ft_printf("declare -x %s\n", envp[index]);
//		else
//		{
//			*equal = '\0';
//			ft_printf("declare -x %s=\"%s\"\n", envp[index], equal + 1);
//		}
//		free(envp[index]);
//		index++;
//	}
//	free(envp);
//	return (0);
//}


//
//int	print_export(t_envp_list *env_variables)
//{
//	char	**envp;
//
//	if ((ft_lstsize_envp(env_variables)) == 1)
//		return (0);
//	envp = get_all_envp(env_variables);
//	if (envp == NULL)
//		return (-1);
//	if (ft_msort_str(envp, 0, ft_split_size(envp) - 1) < 0)
//	{
//		ft_free_split(envp);
//		return (-1);
//	}
//	return (print_env_variables_export(envp));
//}
//
