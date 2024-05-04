/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:57:05 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/04 23:54:04 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	close_all_fds(void)
{
	if (STDIN_FILENO >= 0)
		close(STDIN_FILENO);
	if (STDOUT_FILENO >= 0)
		close(STDOUT_FILENO);
	if (STDERR_FILENO >= 0)
		close(STDERR_FILENO);
}

void	free_strs(t_minishell *minishell)
{
	free_safely_str(&(minishell->user_input));
}

void	free_safely_str(char **str_to_free)
{
	if (*str_to_free != NULL)
	{
		free(*str_to_free);
		*str_to_free = NULL;
	}
}

void	ft_free_tab(char ***tab)
{
	size_t	i;

	i = 0;
	if (!tab || !*tab)
		return ;
	while ((*tab)[i])
	{
		free_safely_str(&((*tab)[i]));
		i++;
	}
	free(*tab);
	*tab = NULL;
}
