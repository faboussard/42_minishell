/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//structure de bbuilint + options
//cd with only a relative or absolute path -> faire un strjoin
//&& transform_to_token->content + 1 == "-n" ->faire un strjoin

#include "lexer.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "../libft/inc/libft.h"
#include "error.h"

bool	define_operator(t_token *new_token, char *string)
{
	int		i;
	int 	operator;
	const char	*operators[OPERATOR_COUNT] = {
		"(", ")", "|", ">", "<", "<<", ">>"
	};

	i = 0;
	while (i < OPERATOR_COUNT)
	{

		if (!ft_strncmp(string, operators[i], ft_strlen(string)))
		{
			define_token(OPERATOR, NO_BUILTIN, operator, new_token);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

//bool	define_operator(t_token *new_token, char *string)
//{
//	int		i;
//	int 	operator;
//	const char	*operators[OPERATOR_COUNT] = {
//		"(", ")", "|", ">", "<", "<<", ">>"
//	};
//
//	i = 0;
//	while (i < OPERATOR_COUNT)
//	{
//		operator = is_operator(string);
//		if (is_operator(string) != -1)
//		{
//			define_token(OPERATOR, NO_BUILTIN, operator, new_token);
//			return (TRUE);
//		}
//		i++;
//	}
//	return (FALSE);
//}

bool	is_redirect_token(t_token *token)
{
	if (token == NULL || token->e_type != OPERATOR)
		return (0);
	return (token->e_operator == INPUT_REDIRECT
			|| token->e_operator == OUTPUT_REDIRECT
			|| token->e_operator == HERE_DOC
			|| token->e_operator == APPEND);
}







