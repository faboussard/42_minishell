/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                             :+:      :+:    :+:  */
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
#include <stdio.h>
#include <stdbool.h>
#include "../libft/inc/libft.h"
#include "minishell.h"

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

void print_token(t_node *list_tokens)
{
	t_node  *iterator;
	t_token *token;

	ft_printf("PRINT LIST\n");
	iterator = list_tokens;
	while (iterator != NULL)
	{
		token = (t_token *)(iterator)->content;
		ft_printf("Type: %d, Builtin: %d, Operator: %d\n", token->e_type, token->e_builtin, token->e_operator);
		iterator = iterator->next;
	}
	ft_printf("\n");
}

void create_double_array(t_minishell *minishell, t_node *list_tokens)
{
	int		count;
	t_node	*current;
	int		i;

	count = ft_lstsize(list_tokens);
	minishell->token_array = malloc((count + 1) * sizeof(char *)); // Add 1 for NULL terminator
	if (minishell->token_array == NULL)
		return ; // ERROR
	current = list_tokens;
	i = 0;
	while (current)
	{
		minishell->token_array[i] = convert_token_to_string(current->content);
		current = current->next;
		i++;
	}
	minishell->token_array[i] = NULL; // Null-terminate the array
}


