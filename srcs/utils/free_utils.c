/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:57:05 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/19 15:54:14 by mbernard         ###   ########.fr       */
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
	free_safely_str(minishell->user_input);
}

void	free_safely_str(char *str_to_free)
{
	if (str_to_free != NULL)
	{
		free(str_to_free);
		str_to_free = NULL;
	}
}

void	ft_free_all_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_tab_from_i(void **tab, int j)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
