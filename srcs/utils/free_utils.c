/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:57:05 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/16 18:09:35 by mbernard         ###   ########.fr       */
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
	if (minishell->user_input)
		free(minishell->user_input);
	if (minishell->current_path)
		free(minishell->current_path);
	if (minishell->old_pwd)
		free(minishell->old_pwd);
}