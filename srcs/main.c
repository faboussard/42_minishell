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

t_node *return_list_tokens(char *string)
{
	t_node 	*list_tokens;

	list_tokens = NULL;
	transform_to_token(string, &list_tokens);
	print_list(list_tokens);
	token_rework(list_tokens);
	print_list(list_tokens);
	return (list_tokens);
}

int main()
{
	char	*string;
	t_node 	*list_tokens_for_exec;

	string = "echo hello >> output.txt";
	list_tokens_for_exec = return_list_tokens(string);
	//ft_lstclear(&list_tokens, &free);
	return (0);
}
