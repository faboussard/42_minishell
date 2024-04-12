/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_readline_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

size_t count_letters_for_space(char *str)
{
	size_t count;

	count = 0;
	while (*str != '\0')
	{
		if (*str != ' ')
			count++;
		str++;
	}
	return (count);
}

size_t count_letters_for_quotes(char *str)
{
	size_t count;

	count = 0;
	while (*str != '\0')
	{
		if (*str != '\"' && *str != '\'')
			count++;
		str++;
	}
	return (count);
}


void deal_double_double_quotes_or_double_single_quotes(char *user_input)
{
	size_t i = 0;
	size_t len = strlen(user_input);

	while (i < len)
	{
		if ((user_input[i] == '\'' && user_input[i + 1] == '\'' && (user_input[i - 1] != '\"')  && (user_input[i + 1] != '\"')) ||
			(user_input[i] == '\"' && user_input[i + 1] == '\"'))
		{
			ft_memmove(&user_input[i], &user_input[i + 2], len - i - 1);
			len -= 2;
			user_input[len] = '\0';
		}
		else
			i++;
	}
}

void *ft_free_all_alloc(char **strs_array, size_t start)
{
	size_t i;

	i = 0;
	while (i < start)
	{
		free(strs_array[i]);
		i++;
	}
	free(strs_array);
	return (NULL);
}

//char	**ft_split_with_quotes_management(t_minishell *minishell, char *string)
//{
//	char	**split;
//	size_t split_size;
//
//	if (string == NULL)
//		return (NULL);
//	split = NULL;
//
//	split = fill_array_with_quotes_management(split, string);
//	return (split);
//}

