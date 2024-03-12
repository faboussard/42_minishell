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

static bool	is_builtin(char *string)
{
	if (!ft_strncmp(string, "echo", ft_strlen(string)) || !ft_strncmp(string, "cd", ft_strlen(string))
		|| !ft_strncmp(string, "ls", ft_strlen(string)) || !ft_strncmp(string, "pwd", ft_strlen(string))
		|| !ft_strncmp(string, "export", ft_strlen(string)) || !ft_strncmp(string, "unset", ft_strlen(string))
		|| !ft_strncmp(string, "env", ft_strlen(string)) || !ft_strncmp(string, "exit", ft_strlen(string)))
		return (TRUE);
	return (FALSE);
}

void define_from_string(t_token *new_token, char *string)
{
	if (is_builtin(string) == TRUE)
		new_token->t_type.e_command = BUILTIN_COMMAND;
}

t_token	*create_token(t_token *token, enum e_token_group group, enum e_token_type type, enum e_token_operators operator)
{
	token->group.e_type = type;
	token->group.e_group = group;
	return (token);
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
	while (*split)
	{
		define_from_string(token, *split);
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




