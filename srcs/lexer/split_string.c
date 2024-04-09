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

 size_t	count_letters_for_space( char *str)
{
	size_t	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str != ' ')
			count++;
		str++;
	}
	return (count);
}

size_t	count_letters_for_quotes( char *str)
{
	size_t	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str != '\"' && *str != '\'')
			count++;
		str++;
	}
	return (count);
}


void deal_double_double_quotes_or_double_single_quotes(char *string)
{
	size_t i;
	size_t len;

	len = strlen(string);
	i = 0;
	while (i < len)
	{
		if ((string[i] == '\'' && string[i + 1] == '\'') || (string[i] == '\"' && string[i + 1] == '\"'))
		{
			ft_memmove(&string[i], &string[i + 1], len - i);
			len--;
		}
		else
		{
			i++;
		}
	}
}

void	*ft_free_all_alloc(char **strs_array, size_t start)
{
	size_t	i;

	i = 0;
	while (i < start)
	{
		free(strs_array[i]);
		i++;
	}
	free(strs_array);
	return (NULL);
}

char **fill_array_with_quotes_management(char *s)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char quote;
	char	**split;
	size_t split_size;

	if (s == NULL)
		return (NULL);
	deal_double_double_quotes_or_double_single_quotes(s);
	split_size = count_letters_for_quotes(s) + 1 + count_letters_for_space(s) + 1;
	split = ft_calloc(split_size, sizeof(char *));
	if (split == NULL)
		return NULL;
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		len = 0;
		if (s[i] && (s[i] == '\"' || s[i] == '\''))
		{
			quote = s[i++];
			while (s[i + len] && s[i + len] != quote)
				len++;
			split[j] = ft_substr(s, i, len);
			if (split[j] == NULL)
			{
				ft_free_all_tab(split);
				return (NULL);
			}
			j++;
			i += len;
			if (s[i] == quote)
				i++;
		}
		else if (s[i] && s[i] != ' ')
		{
			while (s[i + len] && s[i + len] != ' ')
				len++;
			split[j] = ft_substr(s, i, len);
			if (split[j] == NULL)
			{
				ft_free_all_tab(split);
				return NULL;
			}
			j++;
			i += len;
		}
		else
			i++;
	}
	split[j] = NULL;
	return (split);
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

