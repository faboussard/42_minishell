/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:26:16 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/13 16:26:32 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include "libft.h"
#include "minishell.h"


enum e_token_type
{
	NO_TYPE = 0,
	COMMAND = 1,
	ARGUMENT = 2,
	IN_FILE = 3,
    OUT_FILE = 4,
    DELIMITER = 5,
	OPERATOR = 6,
    SUBSHELL = 7,
};

enum e_token_operators
{
	NO_OPERATOR = 0,
	OPEN_PARENTHESES = 1,
	CLOSE_PARENTHESES = 2,
	PIPE = 3,
    OUTPUT_REDIRECT = 4,
	INPUT_REDIRECT = 5,
	HERE_DOC = 6,
	APPEND = 7,
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

typedef struct s_token
{
    char					*name;
    enum e_token_type		e_type;
    enum e_token_builtin	e_builtin;
    enum e_token_operators	e_operator;
    struct s_token          *next;
}	t_token;

char	**split_with_quotes_management(char *string);

int	parentheses_error(const char *string);
int parentheses_on_arg(char *string);


void	define_token_types(enum e_token_type type, enum e_token_builtin builtin, enum e_token_operators operator, t_token *new_token);

bool	get_builtin_token(t_token *new_token, char *string);

/********************* count *********************/

size_t total_commands(t_token *head);
size_t count_letters_until_pipe(t_token *head);
size_t count_cmds_until_pipe(t_token *head);

#endif //LEXER_H
