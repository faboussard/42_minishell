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

/****************** 1. tree top - GROUP ******************/

enum e_token_type
{
	COMMAND = 1,
	ARGUMENT = 2,
	ENVIRONMENT = 3,
	OPERATOR = 4
};

/****************** 2. tree node - TYPE ******************/

enum e_token_command
{
	BUILTIN_COMMAND = 0,
	PATH_COMMAND = 1
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
	APPEND = 7,
	GUILLEMET = 8
};

/****************** 3. tree leaf******************/

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

//voir comment mettre les structures sous forme darbre . le groupe doit contenir les commandes et elles meme les param
typedef struct s_token_type
{
	enum e_token_type	e_type;
	enum e_token_builtin e_builtin;
	enum e_token_command e_command;
	enum e_token_operators e_operator;
} s_token_type;

typedef struct s_token
{
	s_token_type	t_type;
	struct s_token	*right;
	struct s_token	*left;
}	t_token;

void new_token( char *string);

#endif //LEXER_H
