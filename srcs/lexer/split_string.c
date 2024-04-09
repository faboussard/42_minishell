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

static size_t	count_letters_for_space(const char *str, char c)
{
	size_t	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str != c)
			count++;
		str++;
	}
	return (count);
}

static size_t	count_letters_for_quotes(const char *str, char double_quote, char single_quote)
{
	size_t	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str != double_quote && *str != single_quote)
			count++;
		str++;
	}
	return (count);
}


static void deal_double_double_quotes_or_double_single_quotes(char *string)
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

static void	*ft_free_all_alloc(char **strs_array, size_t start)
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

static char **fill_array_with_quotes_management(char **strs_array, const char *s, t_quotes_struct *quotes)
{
	size_t	i;
	size_t	j;
	size_t	len_space;
	size_t	len_quote;

	i = 0;
	j = 0;

	while (s[i] != '\0')
	{
		len_quote = 0;
		if (s[i] && s[i] == quotes->double_quote)
		{
			i++;
			while (s[i + len_quote] && s[i + len_quote] != quotes->double_quote)
				len_quote++;
			strs_array[j] = ft_substr(s, i, len_quote);
			if (strs_array[j] == NULL)
				return (ft_free_all_tab(strs_array), NULL);
			j++;
			i += len_quote;
		}
		else if (s[i] && s[i] == quotes->single_quote)
		{
			i++;
			while (s[i + len_quote] && s[i + len_quote] != quotes->single_quote)
				len_quote++;
			strs_array[j] = ft_substr(s, i, len_quote);
			if (strs_array[j] == NULL)
				return (ft_free_all_alloc(strs_array, j), NULL);
			j++;
			i += len_quote;
		}
		else if (s[i] && s[i] != quotes->space )
		{
			len_space = 0;
			while (s[i + len_space] && s[i + len_space] != quotes->space )
				len_space++;
			strs_array[j] = ft_substr(s, i, len_space);
			if (strs_array[j] == NULL)
				return (ft_free_all_alloc(strs_array, j), NULL);
			j++;
			i += len_space;
		}
		else
			i++;
	}
	strs_array[j] = NULL;
	return (strs_array);
}


char	**ft_split_with_quotes_management(t_minishell *minishell, char *string)
{
	char	**split;

	t_quotes_struct quotes;

	ft_bzero(&quotes, sizeof(t_quotes_struct));
	quotes.single_quote = '\'';
	quotes.double_quote = '\"';
	quotes.space = ' ';
	if (string == NULL)
		return (NULL);
	deal_double_double_quotes_or_double_single_quotes(string);
	split = malloc(sizeof(char **) * (count_letters_for_quotes(string, quotes.double_quote, quotes.single_quote) + count_letters_for_space(string, quotes.space ) + 2));
	if (split == NULL)
		exit_msg(minishell, "Malloc failed at malloc for split", 2);
	split = fill_array_with_quotes_management(split, string, &quotes);
	return (split);
}


//static void deal_single_and_double_quotes_togeter(char *joined_cmd)
//{
//	size_t i;
//	bool end_of_arg;
//
//	i = 0;
//	end_of_arg = 0;
//	while (joined_cmd[i])
//	{
//		if (joined_cmd[i] == '\'' && joined_cmd[i - 1] == '\"' && !end_of_arg)
//			break;
//		if (joined_cmd[i] == '\'' && (joined_cmd[i - 1] != '\"' || end_of_arg))
//		{
//			joined_cmd[i] = '\"';
//			end_of_arg = 1;
//		}
//		i++;
//	}
//}


