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



static void deal_with_quotations_marks(char *joined_cmd)
{
	size_t i;
	bool end_of_arg;

	i = 0;
	end_of_arg = 0;
	while (joined_cmd[i])
	{
		if (joined_cmd[i] == '\'' && joined_cmd[i - 1] == '\"' && !end_of_arg)
			break;
		if (joined_cmd[i] == '\'' && (joined_cmd[i - 1] != '\"' || end_of_arg))
		{
			joined_cmd[i] = '\"';
			end_of_arg = 1;
		}
		i++;
	}
}

char **split_with_quotes(t_minishell *minishell)
{
	char *begin;
	char *joined_string;
	char **split;
	size_t i;
	char *string;

	string = minishell->user_input;
	i = 0;
	while (string[i] && string[i] != '\'' && string[i] != '\"')
		i++;
	if (string[i] == '\0')
	{
		split = ft_split(string, ' ');
		if (!split)
			return (NULL);
		return (split);
	}

	i = 0;
	while (string[i] == ' ')
		i++;
	string = ft_substr(string, i, ft_strlen(string) - i);
	if (string == NULL)
		return (NULL);

	begin = malloc(sizeof(char) * i);
	if (!begin)
		return (NULL);
	//on sepqre lq ou ya des espqces si jqmqis begin nest pas encadre de guillemets 5mot begin).
	// puis on fait split sur les guillemets
	ft_strlcpy(begin, string, i);
	joined_string = ft_strjoin(begin, string + i);
	free(begin);
	if (!joined_string)
		return (NULL);
	deal_with_quotations_marks(joined_string);
	split = ft_split(string,  '\'');
	free(joined_string);
	if (!split)
		return (NULL);
	i = 0;

	//split sur espaces
	while (split[i])
	{
		if (ft_strchr(split[i], '\'') == 0 && ft_strchr(split[i], '\"') == 0 && !ft_strnstr_and_check(string, split[i], ft_strlen(string)))
		{
			char **temp = ft_split(split[i], ' '); // Split sur les espaces
			if (!temp)
				return NULL;
			int k = 0;
			int temp_size = 0;
			while (temp[k])
			{
				temp_size++;
				k++;
			}
			split = realloc(split, (i + temp_size + 1) * sizeof(char *)); // Augmenter la taille du tableau
			if (!split)
			{
				// Gestion de l'échec de la réallocation mémoire
				perror("Erreur lors de la réallocation de mémoire");
				return (NULL);
			}
			k = 0;
			while (temp[k])
			{
				split[i++] = temp[k++];
			}
			free(temp);
		}
		i++;
	}
	split[i] = NULL;
	return (split);
}

	char **split_with_quotes_management(t_minishell *minishell)
	{
		char **split;

		split = split_with_quotes(minishell);
		if (split == NULL)
			return (NULL);
		return (split);
	}


