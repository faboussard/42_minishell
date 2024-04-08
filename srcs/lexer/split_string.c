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

//static void	deal_with_quotations_marks(char *joined_cmd)
//{
//	size_t	i;
//	bool	end_of_arg;
//
//	i = 0;
//	end_of_arg = 0;
//	while (joined_cmd[i])
//	{
//		if (joined_cmd[i] == '\'' && joined_cmd[i - 1] == '\"' && !end_of_arg)
//			break ;
//		if (joined_cmd[i] == '\'' && (joined_cmd[i - 1] != '\"' || end_of_arg))
//		{
//			joined_cmd[i] = '\"';
//			end_of_arg = 1;
//		}
//		i++;
//	}
//}
//
//char	**split_with_quotes(char *string)
//{
//	char	*begin;
//	char	*joined_string;
//	char 	**split;
//	size_t	i;
//
//	i = 0;
//	while (string[i] && string[i] != ' ')
//		i++;
//	i++;
//	begin = malloc(sizeof(char) * i);
//	if (!begin)
//		return (NULL);
//	ft_strlcpy(begin, string, i);
//	joined_string = ft_strjoin(begin, string + i);
//	free(begin);
//	if (!joined_string)
//		return (NULL);
//	deal_with_quotations_marks(joined_string);
//	split = ft_split(joined_string, '\"');
//	free(joined_string);
//	if (!split)
//		return (NULL);
//	return (split);
//}
//
//char	**split_with_quotes_management(char *string)
//{
//	size_t	i;
//	char **split;
//
//	i = 0;
//	while (string[i] && string[i] != '\'' && string[i] != '\"')
//		i++;
//	if (!string[i])
//		split = ft_split(string, ' ');
//	else
//		split = split_with_quotes(string);
//	if (split == NULL)
//		return (NULL);
//	return (split);
//}


//static void	*ft_free_all_alloc_new(char **strs_array, size_t start)
//{
//	size_t	i;
//
//	i = 0;
//	while (i < start)
//	{
//		free(strs_array[i]);
//		i++;
//	}
//	free(strs_array);
//	return (NULL);
//}

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


static char	**fill_array_with_strings(char **strs_array, const char *s, char space, char double_quote, char single_quote)
{
	size_t	i;
	size_t	j;
	size_t	len_space;
	size_t	len_quote;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		len_space = 0;
		len_quote = 0;
		if (s[i] &&s[i] == double_quote || s[i] == single_quote)
		{
			i++;
			while (s[i + len_quote] && s[i + len_quote] != double_quote && s[i + len_quote] != single_quote)
				len_quote++;
			strs_array[j] = ft_substr(s, i, len_quote);
			if (strs_array[j] == NULL)
				return (ft_free_all_tab(strs_array), NULL);
			j++;
			i += len_quote;
		}
		if (s[i] && s[i] != space && s[i] != double_quote && s[i] != single_quote)
		{
			while (s[i + len_space] && s[i + len_space] != space && s[i + len_space] != double_quote && s[i + len_space] != single_quote)
				len_space++;
			strs_array[j] = ft_substr(s, i, len_space);
			if (strs_array[j] == NULL)
				return (ft_free_all_tab(strs_array), NULL);
			j++;
			i += len_space;
		}
		else if(s[i])
			i++;
	}
	strs_array[j] = NULL;
	return (strs_array);
}

char	**ft_split_with_quotes(char const *s, char space, char double_quote, char single_quote)
{
	char	**split;

	if (s == NULL)
		return (NULL);
	split = malloc(sizeof(char **) * (count_letters_for_quotes(s, double_quote, single_quote) + count_letters_for_space(s, space) + 2));
	if (split == NULL)
		return (NULL);
	split = fill_array_with_strings(split, s, space, double_quote, single_quote);
	if (split == NULL)
	{
		free(split);
		return (NULL);
	}
	return (split);
}


//static void deal_with_quotations_marks(char *joined_cmd)
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

char **split_with_quotes(t_minishell *minishell)
{
	char **split;
	char *string;

	string = minishell->user_input;
//	deal_with_quotations_marks(string);
	split = ft_split_with_quotes(string, ' ', '\"', '\'');
	if (!split)
		return (NULL);
	return (split);
}

	char **split_with_quotes_management(t_minishell *minishell)
	{
		char **split;

		split = split_with_quotes(minishell);
		if (split == NULL)
			exit_msg(minishell, "Malloc failed at split_with_quotes_management", -1);
		return (split);
	}


