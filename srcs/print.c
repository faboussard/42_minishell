/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:43:37 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/19 09:43:37 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

void print_array(char **array)
{
	ft_printf("------------------- PRINT ARRAY ------------------------------------\n");
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
}

void print_token(t_node *list_tokens)
{
	t_node  *iterator;
	t_token *token;

	ft_printf("----------------------- PRINT LIST -----------------------\n");
	iterator = list_tokens;
	while (iterator != NULL)
	{
		token = (t_token *)(iterator)->content;
		ft_printf("Name : %s, Type: %d, Builtin: %d, Operator: %d\n", token->name, token->e_type, token->e_builtin, token->e_operator);
		iterator = iterator->next;
	}
	ft_printf("\n");
}
