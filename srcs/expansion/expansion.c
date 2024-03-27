/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include "error.h"

int parentheses_error(const char *string)
{
	int 	i;
	size_t	open_parentheses;
	size_t	close_parentheses;
	i = 0;
	open_parentheses = 0;
	close_parentheses = 0;
	while (string[i])
	{
		open_parentheses += string[i] == '(';
		close_parentheses += string[i] == ')';
		i++;
	}
	if (close_parentheses > open_parentheses)
		return (print_error("syntax error near unexpected token `)'"), -1);
	return (0);
}

int parentheses_on_arg(char *string)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (string[i])
	{
		if (string[i] == '(' && string[i + 1] == '-')
		{
			count = 1;
			break;
		}
		i++;
	}
	if (count == 1)
	{
		string = ft_substr(string, i, ft_strlen(string) - i);
		string = ft_strtrim(string, "(");
		string = ft_strtrim(string, ")");
		ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
		ft_putstr_fd(string, STDERR_FILENO);
		return (-1);
	}
	return (0);
}
