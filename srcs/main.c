/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                		                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/22 12:10:15 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/inc/libft.h"
#include "../includes/lexer.h"
#include "lexer.h"
#include "parser.h"

int main()
{
	char	*string;
	t_node 	*list_tokens;

	list_tokens = NULL;
	string = "<< ( la";
	transform_to_token(string, &list_tokens);
	print_list(list_tokens);
	requalification(list_tokens);
	print_list(list_tokens);
	ft_lstclear(&list_tokens, &free);
}
