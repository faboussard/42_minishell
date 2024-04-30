/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:26:16 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/09 14:54:34 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include "minishell.h"
# include <stdbool.h>


typedef struct s_minishell	t_minishell;

enum						e_token_type
{
	NO_TYPE = 0,
	COMMAND = 1,
	ARGUMENT = 2,
	IN_FILE = 3,
	OUT_FILE = 4,
	DELIMITER = 5,
	APPEND_FILE = 6,
	OPERATOR = 7,
	TO_DELETE = 8
};

enum						e_token_operators
{
	NO_OPERATOR = 0,
	OPEN_PARENTHESES = 1,
	CLOSE_PARENTHESES = 2,
	PIPE = 3,
	OUTPUT_REDIRECT = 4,
	INPUT_REDIRECT = 5,
	HERE_DOC = 6,
	APPEND = 7,
	DOUBLE_QUOTE = 8,
	SINGLE_QUOTE = 9,
	IS_SPACE = 10,
	DOLLAR = 11
};

enum						e_token_builtin
{
	NO_BUILTIN = 0,
	CD = 1,
	ECHO = 2,
	PWD = 3,
	EXPORT = 4,
	UNSET = 5,
	ENV = 6,
	EXIT = 7
};

typedef struct s_token
{
	char					*name;
	enum e_token_type		e_type;
	enum e_token_builtin	e_builtin;
	enum e_token_operators	e_operator;
	bool					is_quoted_delimiter;
	struct s_token			*next;
}							t_token_list;

/********************* tokenization.c *********************/

void transform_to_token(t_minishell *minishell, char *string, t_token_list **list);
void create_token(t_minishell *minishell, char *string, t_token_list **list);
void				define_token_types(enum e_token_type type,
						enum e_token_builtin builtin,
						enum e_token_operators operator,
						t_token_list *token);
bool				get_builtin_token(t_token_list *new_token,
						char *string);
bool	char_is_operator(char c);
bool	is_redirect_token_or_pipe(t_token_list *token);

/********************* token_utils.c *********************/
void del_next_token(t_token_list **token);
void remove_node_token(t_token_list **begin_list, t_token_list *node_to_remove);
int define_token(t_token_list *new_token, char *string);

/********************* count_tokens.c *********************/

int count_token_by_operator(t_minishell *minishell, enum e_token_operators operator_type);
size_t				count_letters_until_pipe(t_token_list *head);
void add_quote_count(t_token_list *iterator, int *s_count, int *d_count);

/********************** check syntax *********************/

bool check_syntax(t_minishell *minishell);

#endif // LEXER_H
