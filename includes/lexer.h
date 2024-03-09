//
// Created by fanny on 09/03/24.
//

#ifndef MINISHELL_LEXER_H
#define MINISHELL_LEXER_H

// macro a malloc
#define MAX_TOKEN_LENGTH 100


typedef enum
{
	ARGUMENT,
	COMMAND,
	ENVIRONMENT
} token_type;

typedef struct
{
	token_type type;
	char value[MAX_TOKEN_LENGTH];
} token_t;

// Structure to store tokenized line
typedef struct
{
	token_t *tokens;
	int count;
} g_line_t;

g_line_t lexer(const char *input);
void free_g_line(g_line_t g_line);

#endif //MINISHELL_LEXER_H
