#include <lexer.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "inc/libft.h"

// Function to check if a character is a delimiter
int is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\0');
}

// Function to add a token to g_line_t
void add_token(g_line_t *g_line, token_type type, char *value)
{
	token_t token;
	token.type = type;
	ft_strlcpy(token.value, value, MAX_TOKEN_LENGTH);
	g_line->tokens[g_line->count++] = token;
}

// Main lexer function
g_line_t lexer(const char *input)
{
	g_line_t g_line;
	int token_start;
	int i;
	token_type type;

	g_line.tokens = malloc(sizeof(token_t) * strlen(input));
	g_line.count = 0;
	i = 0;
	while (input[i] != '\0')
	{
		while (is_delimiter(input[i]))
			i++;
		if (input[i] == '\0')
			break;
		token_start = i;
		if (input[i] == '$')
			type = ENVIRONMENT;
		else if (isalpha(input[i]))
			type = COMMAND;
		else
			type = ARGUMENT;
		while (!is_delimiter(input[i]) && input[i] != '\0')
			i++;
		int token_length = i - token_start;
		char token_value[MAX_TOKEN_LENGTH];
		ft_strlcpy(token_value, input + token_start, token_length);
		token_value[token_length] = '\0';
		add_token(&g_line, type, token_value);
	}
	return g_line;
}

// Function to free memory allocated for g_line_t
void free_g_line(g_line_t g_line)
{
	free(g_line.tokens);
}



