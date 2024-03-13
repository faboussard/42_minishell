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
	int		i;
	char	builtins[8][10];

	ft_strcpy(builtins[LS], "ls");
	ft_strcpy(builtins[ECHO], "echo");
	ft_strcpy(builtins[CD], "cd");
	ft_strcpy(builtins[PWD], "pwd");
	ft_strcpy(builtins[EXIT], "exit");
	ft_strcpy(builtins[ENV], "env");
	ft_strcpy(builtins[EXPORT], "export");
	ft_strcpy(builtins[UNSET], "unset");
	i = 0;
	while (i++ < 8)
	{
		if (!ft_strncmp(string, builtins[i], ft_strlen(string)))
		{
			new_token->t_type.e_builtin = i;
			new_token->t_type.e_command = BUILTIN_COMMAND;
			new_token->t_type.e_type = COMMAND;
			return (TRUE);
		}
	}
	return (FALSE);
}

//static bool	define_operator(t_token *new_token, char *string)
//{
//	if (!ft_strncmp(string, "|", ft_strlen(string)))
//		new_token->t_type.e_operator = PIPE;
//	if (!ft_strncmp(string, ">>", ft_strlen(string)))
//		new_token->t_type.e_operator = HERE_DOC;
//	if (!ft_strncmp(string, ";", ft_strlen(string)))
//		new_token->t_type.e_operator = GUILLEMET;
//	if 	(!ft_strncmp(string, ">", ft_strlen(string)))
//		new_token->t_type.e_operator = INPUT_REDIRECT;
//	if (!ft_strncmp(string, "<", ft_strlen(string)))
//		new_token->t_type.e_operator = OUTPUT_REDIRECT;
//	if (!ft_strncmp(string, ("("), ft_strlen(string)))
//		new_token->t_type.e_operator = OPEN_PARENTHESES;
//	if (!ft_strncmp(string, (")"), ft_strlen(string)))
//		new_token->t_type.e_operator = CLOSE_PARENTHESES;
//	if (!ft_strncmp(string, ("&"), ft_strlen(string)))
//		new_token->t_type.e_operator = APPEND;
//	if (new_token->t_type.e_operator > 0)
//	{
//		new_token->t_type.e_type = OPERATOR;
//		return (TRUE);
//	}
//	return (FALSE);
//}

//static bool	define_arg(t_token *new_token, char *string)
//{
//	if (string[0] == '-')
//	{
//		new_token->t_type.e_type = ARGUMENT;
//		return (TRUE);
//	}
//	return (FALSE);
//}

void define_from_string(t_token *new_token, char *string)
{
	if (define_builtin(new_token, string) == TRUE)
	{
		printf("here is builtin : %d\n", new_token->t_type.e_builtin);
		printf("here is type for builtin : %d\n", new_token->t_type.e_type);
		//creer le token a la bonne place dans larbre
	}
//	if (define_operator(new_token, string) == TRUE)
//	{
//		printf("here is operator : %d\n", new_token->t_type.e_operator);
//		printf("here is type for operator : %d\n", new_token->t_type.e_type);
//		//creer le token a la bonne place dans larbre
//	}
//	if (define_arg(new_token, string) == TRUE)
//	{
//		printf("here is type arg : %d\n", new_token->t_type.e_type);
//		//crrer le token q lq bonne plqce dqns larbre
//	}
//	else
//	{
//		(new_token->t_type.e_type = COMMAND);
//		printf("here is type command : %d\n", new_token->t_type.e_type);
//		//crrer le token q lq bonne plqce dqns larbre
//	}
//	//return ?
//
//	else
//		//creer le token command (un alpha)
//}
//fedine  <<{delimiter}

//void define_token_type(t_token *new_token)
//{
//	if (new_token->group.e_type == DELIMITER
//					|| new_token->group.e_type == PATH)
//}
}

// Function to add a token. objectif : tous les token sont bine dans la struc et saffichent bien.
void new_token( char *string)
{
	int 	i;
	t_token	token;
	//ajouter une condition pour faire le split que sil ny a pas despace avec des guillets. sinon on retirera ce token avant de resplit.
	char	**split;

	split = ft_split(string, ' ');
	if (split == NULL)
		return;

	i = 0;
	while (split[i])
	{

		ft_memset(&token, 0, sizeof(t_token));
		define_from_string(&token, split[i]);
//		define_token_type(token);
		printf("here is builtin : %d\n", token.t_type.e_builtin);
		printf("here is type for builtin : %d\n", token.t_type.e_type);;
//		define_token_group(token);
//		add_token_to_tre(token);
// 		free(token); bien verifier aue les enum du token soit a 0
		i++;
	}
}

//void add_token_to_list(t_token new_token)
//{
//}




