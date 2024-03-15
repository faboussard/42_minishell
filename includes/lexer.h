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

#include <stdbool.h>
#include "libft.h"

enum e_token_type
{
	NO_TYPE = 0,
	COMMAND = 1,
	ARGUMENT = 2,
	PATH_FILE = 3,
	OPERATOR = 4,
	TO_APPEND = 5,
	SUBSHELL = 6,
};

enum e_token_subtype
{
	NO_SUBTYPE = 0,


	BEGIN_SUBSHELL = 3
};

// pour lenveronnement ca provint du path voir apres

enum e_token_operators
{
	NO_OPERATOR = 0,
	OPEN_PARENTHESES = 1,
	CLOSE_PARENTHESES = 2,
	PIPE = 3,
	INPUT_REDIRECT = 4,
	OUTPUT_REDIRECT = 5,
	HERE_DOC = 6,
	APPEND = 7,
	DOUBLE_QUOTE = 8,
	SINGLE_QUOTE = 9,
};

enum e_token_builtin
{
	NO_BUILTIN = 0,
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
	enum e_token_type		e_type;
	enum e_token_builtin	e_builtin;
	enum e_token_operators	e_operator;
}	t_token;

/****************** LEXER ******************/

void	transform_to_token(char *string, t_node **list_tokens);
void	print_list(t_node *list_tokens);
void	define_token(enum e_token_type type, enum e_token_builtin builtin, enum e_token_operators operator, t_token *new_token);


/****************** OPERATORS ******************/

bool	define_operator(t_token *new_token, char *string);
bool	is_redirect_token(t_token *token);
void	print_operator_syntax_error(t_token *token);


/****************** BUILTIN ******************/
void	cpy_string_builtin(char builtins[7][10]);
bool	define_builtin(t_token *new_token, char *string);

#endif //LEXER_H
