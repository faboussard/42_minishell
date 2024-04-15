/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:32:23 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/15 14:00:20 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_minishell *minishell)
{
	char	cwd[PATH_MAX];

	if (minishell->current_path != NULL)
	{
		printf("%s\n", minishell->current_path);
		return (0);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("minishell: getcwd");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
