/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                               		        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/22 12:10:15 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//structure de bbuilint + options
//cd with only a relative or absolute path
#include "../includes/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "../libft/inc/libft.h"

// Function to check if a character is a delimiter
int is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\0');
}

void define_from_string(t_token *token)
{
	if (token->content == "echo" || (token->content == "cd" && token->content + 1 == "-n") || token->content == "pwd"
		|| token->content == "export" || token->content == "unset" || token->content == "env"
		|| token->content == "exit")
		token->group.e_type = builtin;
	if ()

}

void define_token_type(t_token *token)
{
	if (token->group.e_type == builtin || token->group.e_type == delimiter
			|| token->group.e_type == redirect || token->group.e_type == pipe
					|| token->group.e_type == path_env)
		token->group.e_group = COMMAND;
//	if (token->group.e_type == builtin || token->group.e_type == delimiter
//		|| token->group.e_type == redirect || token->group.e_type == pipe
//		|| token->group.e_type == path_env)
//		token->group.e_group = ARGUMENT;
}

// Function to add a token. objectif : tous les token sont bine dans la struc et saffichent bien.
void new_token(t_token new_token, char *string)
{
	//ajouter une condition pour faire le split que sil ny a pas despace avec des guillets. sinon on retirera ce token avant de resplit.
	char	**split;
	t_token	token;
	int 	i;

	i = 0;
	split = ft_split(string, ' ');
	ft_memset(&token, 0, sizeof(t_token));
	while (split[i])
	{
		token.content = split[i];
		define_from_string(&token);
		define_token_type(&token);
		define_token_group(&token);
		add_token_to_list(&token);
		i++;
	}
}

//void add_token_to_list(t_token new_token)
//{
//}




