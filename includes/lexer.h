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

typedef struct s_minishell t_minishell;


enum e_token_type
{
	NO_TYPE = 0,
	COMMAND = 1,
	ARGUMENT = 2,
	IN_FILE = 3,
    OUT_FILE = 4,
    DELIMITER = 5,
	APPEND_FILE = 6,
	OPERATOR = 7,
    SUBSHELL = 8,
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
	ECHO = 2,
	PWD = 3,
	EXPORT = 4,
	UNSET =	5,
	ENV = 6,
	EXIT = 7
};

typedef struct s_token
{
    char					*name;
    enum e_token_type		e_type;
    enum e_token_builtin	e_builtin;
    enum e_token_operators	e_operator;
    struct s_token          *next;
}	t_token_list;


char	**split_with_quotes_management(char *string);

/********************* tokenization *********************/

void	transform_to_token(t_minishell *minishell, char **split);
void	define_token_types(enum e_token_type type, enum e_token_builtin builtin, enum e_token_operators operator, t_token_list *new_token);
bool	get_builtin_token(t_token_list *new_token, char *string);

/********************* count *********************/

void count_total_commands(t_minishell *minishell);
size_t count_letters_until_pipe(t_token_list *head);
size_t count_cmds_until_pipe(t_token_list *head);

/********************** check syntax *********************/

int check_syntax(t_minishell *minishell);



#endif //LEXER_H
