/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                               		        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/22 12:10:15 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#include "libft.h"

enum e_token_type
{
	COMMAND = 1,
	ARGUMENT = 2,
	ENVIRONMENT = 3,
	OPERATOR = 4
};

// pour lenveronnement ca provint du path voir apres

enum e_token_operators
{
	OPEN_PARENTHESES = 0,
	CLOSE_PARENTHESES = 1,
	PIPE = 2,
	INPUT_REDIRECT = 3,
	OUTPUT_REDIRECT = 4,
	HERE_DOC = 5,
	DOUBLE_QUOTE = 6,
	SINGLE_QUOTE = 7,
};

enum e_token_builtin
{
	CD = 0,
	LS = 1,
	ECHO = 2,
	PWD = 3,
	EXPORT = 4,
	UNSET =	5,
	ENV = 6,
	EXIT = 7
};

/****************** STRCUTURES ******************/

typedef struct s_token
{
	enum e_token_type	e_type;
	enum e_token_builtin e_builtin;
	enum e_token_operators e_operator;
}	t_token;

void	transform_to_token(char *string, t_node **list_tokens);
void	print_list(t_node *list_tokens);

#endif //LEXER_H
