/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/27 10:33:17 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdlib.h>

void	create_token(t_minishell *minishell, char *string, t_token_list **list)
{
	t_token_list	*new_token;

	new_token = ft_calloc(1, sizeof(t_token_list));
	if (new_token == NULL)
	{
		free_safely_str(&string);
		exit_msg(minishell, "Malloc failed at create_token", ENOMEM);
	}
	if (define_token(new_token, string) == MALLOC_FAILED)
	{
		free_safely_str(&string);
		free(new_token);
		exit_msg(minishell, "Malloc failed at create_token", ENOMEM);
	}
	add_token_to_list(list, new_token);
}

static void	create_words(char *string, int *i, char **temp)
{
	int	j;

	j = 0;
	while (string[*i] && (ft_isalnum(string[*i]) || string[*i] == '_'))
		(*temp)[j++] = string[(*i)++];
	(*temp)[j] = '\0';
}

void	transform_to_token(t_minishell *m, char *string, t_token_list **list)
{
	int		i;
	char	*temp;
	size_t	len;

	i = 0;
	len = ft_strlen(string) + 1;
	while (string[i])
	{
		temp = ft_calloc(1, len);
		if (temp == NULL)
			exit_msg(m, "Malloc failed at transform_to_token", ENOMEM);
		if ((ft_isspace(string[i]) || !ft_isalnum(string[i]))
			&& string[i] != '_')
		{
			temp[0] = string[i];
			i++;
		}
		else if (string[i])
			create_words(string, &i, &temp);
		create_token(m, temp, list);
		free_safely_str(&temp);
	}
}
