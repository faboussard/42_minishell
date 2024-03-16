/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                               		        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/22 12:10:15 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "general.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "../libft/inc/libft.h"

void	ft_free_split(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_tab(void **tab, int j)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	print_error(const char *error)
{
	if (error != NULL)
		ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	print_operator_syntax_error(t_token *token)
{
	enum e_token_operators	error;

	if (token == NULL)
		return (print_error("syntax error near unexpected token `newline'"));
	error = token->e_operator;
	if (error == OPEN_PARENTHESES)
		print_error("syntax error near unexpected token `('");
	else if (error == CLOSE_PARENTHESES)
		print_error("syntax error near unexpected token `)'");
	else if (error == PIPE)
		print_error("syntax error near unexpected token `|'");
	else if (error == INPUT_REDIRECT)
		print_error("syntax error near unexpected token `<'");
	else if (error == OUTPUT_REDIRECT)
		print_error("syntax error near unexpected token `>'");
	else if (error == HERE_DOC)
		print_error("syntax error near unexpected token `<<'");
	else if (error == APPEND)
		print_error("syntax error near unexpected token `>>'");
}


