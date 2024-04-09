/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
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


void identify_envp_token(t_token_list *token, t_minishell *minishell)
{
	t_envp_list *iterator;

	iterator = minishell->list_envp;
	while (iterator != NULL)
	{
		if (ft_strcmp(token->name, iterator->target) == 0)
		{
			char *old_name = token->name; // Stocker l'ancienne valeur de token->name
			token->name = ft_strdup(iterator->value);
			if (token->name == NULL)
			{
				free(old_name);
				exit_msg(minishell, "Malloc failed at identify_envp_token", -1);
			}
			free(old_name);
			break;
		}
		iterator = iterator->next;
	}
}


void ignore_next_char(char *str, char c)
{
	char *char_to_ignore;
	size_t len;

	char_to_ignore = strchr(str, c);
	if (char_to_ignore != NULL)
	{
		len = strlen(char_to_ignore);
		ft_memmove(char_to_ignore, char_to_ignore + 1, len);
		char_to_ignore[len - 1] = '\0';
	}
}

void ignore_equal_sign_envp(t_minishell *minishell)
{
	t_envp_list *iterator = minishell->list_envp;
	while (iterator != NULL)
	{
		ignore_next_char(iterator->target, '=');
		iterator = iterator->next;
	}
}

void ignore_dollar_token(t_token_list *token, t_minishell *minishell)
{
	char *new_name;
	size_t len;

	if (token->name != NULL)
	{
		len = strlen(token->name);
		new_name = malloc(len);
		if (new_name == NULL)
			exit_msg(minishell, "Malloc failed at ignore_dollar", -1);
		ft_memcpy(new_name, token->name + 1, len);
		free(token->name);
		token->name = new_name;
	}
}

void expand_dollar_token(t_token_list *token, t_minishell *minishell)
{
	char *original_name;

	original_name = strdup(token->name);
	if (original_name == NULL)
		exit_msg(minishell, "Malloc failed at expand_dollar_token", -1);
	ignore_dollar_token(token, minishell);
	ignore_equal_sign_envp(minishell);
	identify_envp_token(token, minishell);
	if (strcmp(original_name, token->name) != 0)
		free(original_name);
}


int	ft_strnstr_and_check(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char previous_char;

	i = 0;
	while (big[i] != '\0')
	{
		j = 0;
		while (big[i + j] == little[j] && ((i + j) < len))
		{
			j++;
			if (j == 1)
				previous_char = big[i - 1];
			if (little[j] == '\0' && previous_char == '\'')
				return (1);
		}
		i++;
	}
	return (0);
}

void expander(t_minishell *minishell)
{
	t_token_list *iterator;

	iterator = minishell->list_tokens;
	while (iterator != NULL)
	{
		if (ft_strcmp(iterator->name, "$?") == 0)
			printf("%d\n", minishell->status);
		if (iterator->e_type != DELIMITER
				&& iterator->name[0] == '$' && iterator->name[1] != '\0'
				&& ft_strnstr_and_check(minishell->user_input, iterator->name
										,ft_strlen(minishell->user_input)) == 0)
			expand_dollar_token(iterator, minishell);
		iterator = iterator->next;
	}
}
