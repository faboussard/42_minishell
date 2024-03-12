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
//cd with only a relative or absolute path -> faire un strjoin
//&& new_token->content + 1 == "-n" ->faire un strjoin

#include "lexer.h"
#include "general.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "../libft/inc/libft.h"

// Function to check if a character is a delimiter
int is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\0');
}

static bool	is_builtin(t_token *new_token)
{
	if (*new_token->content == "echo" || new_token->content == "cd" || new_token->content == "pwd"
		|| new_token->content == "export" || new_token->content == "unset" || new_token->content == "env"
		|| new_token->content == "exit")
		return (TRUE);
	return (FALSE);
}

void define_from_string(t_token *new_token)
{
	if (is_builtin == TRUE)
	new_token->group.e_type = BUILTIN;
}

void define_token_type(t_token *new_token)
{
	if (new_token->group.e_type == BUILTIN || new_token->group.e_type == DELIMITER
			|| new_token->group.e_type == REDIRECT || new_token->group.e_type == pipe
					|| new_token->group.e_type == PATH)
		new_token->group.e_group = COMMAND;
//	if (token->group.e_type == builtin || token->group.e_type == delimiter
//		|| token->group.e_type == redirect || token->group.e_type == pipe
//		|| token->group.e_type == path_env)
//		token->group.e_group = ARGUMENT;
	identify_token(new_token, e_token);
}

// Function to add a token. objectif : tous les token sont bine dans la struc et saffichent bien.
void new_token( char *string)
{
	//ajouter une condition pour faire le split que sil ny a pas despace avec des guillets. sinon on retirera ce token avant de resplit.
	char	**split;
	t_token	*token;
	int 	i;

	i = 0;
	split = ft_split(string, ' ');
//	if (split == NULL)
//		raise_error(MALLOC_FAILURE);
	ft_memset(&token, 0, sizeof(t_token));
	while (split[i])
	{
		token->content = split[i];
		define_from_string(token);
		define_token_type(token);

		printf("token groupe is %s and tocken type is %s\n", token->group.e_group, token->group.e_type);
//		define_token_group(token);
//		add_token_to_list(token);
		i++;
	}
}

//void add_token_to_list(t_token new_token)
//{
//}




