/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_table.c		                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
size_t calculate_total_target_size(t_minishell *minishell)
{
	size_t target_size = 0;
	t_node *current_node = minishell->list_envp;

	while (current_node != NULL)
	{
		t_envp_content *content = (t_envp_content *)current_node->content;
		target_size += content->target_size;
		current_node = current_node->next;
	}
	return target_size;
}

size_t calculate_total_value_size(t_minishell *minishell)
{
	size_t value_size = 0;
	t_node *current_node = minishell->list_envp;

	while (current_node != NULL)
	{
		t_envp_content *content = (t_envp_content *)current_node->content;
		value_size += content->value_size;
		current_node = current_node->next;
	}
	return value_size;
}

size_t calculate_total_size(t_minishell *minishell)
{
	size_t value_size = calculate_total_value_size(minishell);
	size_t target_size = calculate_total_target_size(minishell);
	return target_size + value_size;
}
