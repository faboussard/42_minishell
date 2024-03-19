/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:43:37 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/19 09:43:37 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdlib.h>
#include "minishell.h"

void	ft_init_minishell(t_minishell *minishell)
{
	ft_bzero(minishell, (sizeof * minishell));
	minishell->status = 0;
	minishell->fd_in = -1;
	minishell->fd_out = -1;
}

void	exit_msg(t_minishell *minishell, char *msg, int error_code)
{
	if (minishell != NULL)
		free_minishell(minishell);
	ft_putendl_fd(msg, 2);
	exit(error_code);
}

t_token *return_last_token(t_node *list_tokens)
{
	t_node *iterator;
	t_token *last_token;

	iterator = list_tokens;
	while (iterator->next != NULL)
		iterator = iterator->next;
	last_token = (t_token *) (iterator)->content;
	return (last_token);
}