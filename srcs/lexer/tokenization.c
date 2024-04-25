/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdlib.h>

void create_token(t_minishell *minishell, char *string)
{
	t_token_list *new_token;

	new_token = ft_calloc(1, sizeof(t_token_list));
	if (new_token == NULL)
	{
		free_safely_str(string);
		exit_msg(minishell, "Malloc failed at create_token", 2);
	}
	if (define_token(new_token, string) == 0)
	{
		free_safely_str(string);
		free(new_token);
		exit_msg(minishell, "Malloc failed at create_token", 2);
	}
	add_token_to_list(&minishell->list_tokens, new_token);
}

static char *add_until_char(char *temp,char *string, int *i)
{
	int		j;

	j = 0;
	while (string[*i] && !char_is_operator(string[*i]))
		temp[j++] = string[(*i)++];
	if (j != 0)
		(*i)--;
	return (temp);
}

static void create_words(t_minishell *minishell, char *string, int *i, char **temp)
{
	int j;

	j = (*i);
	while (string[j] && !char_is_operator(string[j]))
		j++;
	(*temp) = add_until_char((*temp), string, i);
	create_token(minishell, (*temp));
	(*i)++;
}

void transform_to_token(t_minishell *minishell, char *string)
{
	int i;
	char *temp;
	size_t len;

	i = 0;
	len = ft_strlen(string) + 1;
	while (string[i])
	{
		temp = ft_calloc(1, len);
		if (temp == NULL)
			exit_msg(minishell, "Malloc failed at transform_to_token", 2);
		if (char_is_operator(string[i]))
		{
			temp[0] = string[i];
			create_token(minishell, temp);
			i++;
		}
		else if (string[i])
			create_words(minishell, string, &i, &temp);
		free_safely_str(temp);
	}
}
