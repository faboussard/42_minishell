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
	OPEN_PARENTHESES = 1,
	CLOSE_PARENTHESES = 2,
	PIPE = 3,
	INPUT_REDIRECT = 4,
	OUTPUT_REDIRECT = 5,
	HERE_DOC = 6,
	DOUBLE_QUOTE = 7,
	SINGLE_QUOTE = 8
};

enum e_token_builtin
{
	CD = 1,
	LS = 2,
	ECHO = 3,
	PWD = 4,
	EXPORT = 5,
	UNSET =	6,
	ENV = 7,
	EXIT = 8
};

/****************** STRCUTURES ******************/


typedef struct s_token
{
	enum e_token_type	e_type;
	enum e_token_builtin e_builtin;
	enum e_token_operators e_operator;
}	t_token;

void new_token( char *string);

#endif //LEXER_H
