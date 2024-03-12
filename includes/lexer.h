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

#ifndef MINISHELL_LEXER_H
#define MINISHELL_LEXER_H

/****************** 1. tree top - GROUP ******************/

typedef enum e_token_type
{
	COMMAND = 0,
	ARGUMENT = 1,
	ENVIRONMENT = 2,
	OPERATOR = 3
} e_token_type;

/****************** 2. tree node - TYPE ******************/

typedef enum e_token_command
{
	BUILTIN_COMMAND = 0,
	PATH_COMMAND = 1
} e_token_command;

// pour lenveronnement ca provint du path voir apres

typedef enum e_token_operators
{
	OPEN_PARENTHESES = 0,
	CLOSE_PARENTHESES = 1,
	PIPE = 2,
	INPUT_REDIRECT = 3,
	OUTPUT_REDIRECT = 4,
	HERE_DOC = 5,
	APPEND = 6
} e_token_operators;

/****************** 3. tree leaf******************/

typedef enum e_token_builtin
{
	CD = 0,
	LS = 1,
	ECHO = 2,
	PWD = 3,
	EXPORT = 4,
	UNSET =	5,
	ENV = 6,
	EXIT = 7
} e_token_builtin;

/****************** STRCUTURES ******************/

//voir comment mettre les structures sous forme darbre . le groupe doit contenir les commandes et elles meme les param
typedef struct s_token_type
{
	e_token_type	e_type;
	e_token_builtin e_builtin;
	e_token_command e_command;
	e_token_operators e_operator;
} s_token_type;

typedef struct s_token
{
	s_token_type	t_type;
	struct s_token	*right;
	struct s_token	*left;
}	t_token;

#endif //MINISHELL_LEXER_H
