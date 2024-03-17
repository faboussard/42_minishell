/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lexer.h"
#include "general.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../libft/inc/libft.h"

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



