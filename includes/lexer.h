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
	NO_TYPE = -1,
	COMMAND = 0,
	ARGUMENT = 1,
	ENVIRONMENT = 2,
	OPERATOR = 3,
	END_WORD = 4
};

// pour lenveronnement ca provint du path voir apres

enum e_token_operators
{
	NO_OPERATOR = -1,
	OPEN_PARENTHESES = 0,
	CLOSE_PARENTHESES = 1,
	PIPE = 2,
	INPUT_REDIRECT = 3,
	OUTPUT_REDIRECT = 4,
	HERE_DOC = 5,
	APPEND = 6,
	DOUBLE_QUOTE = 7,
	SINGLE_QUOTE = 8,
};

enum e_token_builtin
{
	NO_BUILTIN = -1,
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
