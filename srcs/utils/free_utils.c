/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:57:05 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/06 14:50:37 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

void	close_all_fds(t_minishell *m, t_process_list *pl)
{
	if (pl != NULL)
		close_fds(pl->fd_in, pl->fd_out);
	if (m != NULL)
	{
		close_fds(m->tmp_in, 0);
		close_pipes(m->pipe_fd);
	}
}
/*	if (STDIN_FILENO >= 0)
		close(STDIN_FILENO);
	if (STDOUT_FILENO >= 0)
		close(STDOUT_FILENO);
	if (STDERR_FILENO >= 0)
		close(STDERR_FILENO);
	Les entrees sorties standard ne doivent pas être fermées
*/

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
