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


static bool	define_builtin(t_token *new_token, char *string)
{
	if (!ft_strncmp(string, "ls", ft_strlen(string)))
		new_token->t_type.e_builtin = LS;
	if (!ft_strncmp(string, "echo", ft_strlen(string)))
		new_token->t_type.e_builtin = ECHO;
	if (!ft_strncmp(string, "cd", ft_strlen(string)))
		new_token->t_type.e_builtin = CD;
	if (!ft_strncmp(string, "pwd", ft_strlen(string)))
		new_token->t_type.e_builtin = PWD;
	if (!ft_strncmp(string, "export", ft_strlen(string)))
		new_token->t_type.e_builtin = EXPORT;
	if (!ft_strncmp(string, "unset", ft_strlen(string)))
		new_token->t_type.e_builtin = UNSET;
	if (!ft_strncmp(string, "env", ft_strlen(string)))
		new_token->t_type.e_builtin = ENV;
	if (!ft_strncmp(string, "exit", ft_strlen(string)))
		new_token->t_type.e_builtin = EXIT;
	if (new_token->t_type.e_builtin > 0)
	{
		new_token->t_type.e_command = BUILTIN_COMMAND;
		new_token->t_type.e_type = COMMAND;
		return (TRUE);
	}
	return (FALSE);
}

static bool	define_operator(t_token *new_token, char *string)
{
	if (!ft_strncmp(string, "|", ft_strlen(string)))
		new_token->t_type.e_operator = PIPE;
	if (!ft_strncmp(string, ">>", ft_strlen(string)))
		new_token->t_type.e_operator = HERE_DOC;
	if (!ft_strncmp(string, ";", ft_strlen(string)))
		new_token->t_type.e_operator = GUILLEMET;
	if 	(!ft_strncmp(string, ">", ft_strlen(string)))
		new_token->t_type.e_operator = INPUT_REDIRECT;
	if (!ft_strncmp(string, "<", ft_strlen(string)))
		new_token->t_type.e_operator = OUTPUT_REDIRECT;
	if (!ft_strncmp(string, ("("), ft_strlen(string)))
		new_token->t_type.e_operator = OPEN_PARENTHESES;
	if (!ft_strncmp(string, (")"), ft_strlen(string)))
		new_token->t_type.e_operator = CLOSE_PARENTHESES;
	if (!ft_strncmp(string, ("&"), ft_strlen(string)))
		new_token->t_type.e_operator = APPEND;
	if (new_token->t_type.e_operator > 0)
	{
		new_token->t_type.e_type = OPERATOR;
		return (TRUE);
	}
	return (FALSE);
}

static bool	define_arg(t_token *new_token, char *string)
{
	if (string[0] == '-')
	{
		new_token->t_type.e_type = ARGUMENT;
		return (TRUE);
	}
	return (FALSE);
}

static bool	define_argument(t_token *new_token, char *string)
{

}

void define_from_string(t_token *new_token, char *string)
{
	if (define_builtin(new_token, string) == TRUE)
	{
		printf("here is builtin : %d\n", new_token->t_type.e_builtin);
		printf("here is type for builtin : %d\n", new_token->t_type.e_type);
		//creer le token a la bonne place dans larbre
	}
	if (define_operator(new_token, string) == TRUE)
	{
		printf("here is operator : %d\n", new_token->t_type.e_operator);
		printf("here is type for operator : %d\n", new_token->t_type.e_type);
		//creer le token a la bonne place dans larbre
	}
	if (define_arg(new_token, string) == TRUE)
	{
		printf("here is type arg : %d\n", new_token->t_type.e_type);
		//crrer le token q lq bonne plqce dqns larbre
	}
	else
	{
		(new_token->t_type.e_type = COMMAND);
		printf("here is type command : %d\n", new_token->t_type.e_type);
		//crrer le token q lq bonne plqce dqns larbre
	}
	//return ?

	else
		//creer le token command (un alpha)
}

void define_token_type(t_token *new_token)
{
	if (new_token->group.e_type == DELIMITER
					|| new_token->group.e_type == PATH)
}

// Function to add a token. objectif : tous les token sont bine dans la struc et saffichent bien.
void new_token( char *string)
{
	int 	i;
	t_token	*token;
	//ajouter une condition pour faire le split que sil ny a pas despace avec des guillets. sinon on retirera ce token avant de resplit.
	char	**split;

	split = ft_split(string, ' ');
//	if (split == NULL)
//		raise_error(MALLOC_FAILURE);

	while (*split)
	{
		i = 0;
		ft_memset(&token, 0, sizeof(t_token));
		define_from_string(token, *split);
		define_token_type(token);
		printf("token groupe is %s and tocken type is %s\n", token->group.e_group, token->group.e_type);
//		define_token_group(token);
//		add_token_to_tre(token);
// 		free(token); bien verifier aue les enum du token soit a 0
		i++;
	}
}

//void add_token_to_list(t_token new_token)
//{
//}




