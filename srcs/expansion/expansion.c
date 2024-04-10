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

int check_equal_position_in_string(char *string, t_envp_list *iterator)
{
	int i;
	int j;

	i = 0;
	j = ft_strlen(iterator->target);
	while (string[i] && string[i] != '=')
		i++;
	if (string[i] == iterator->target[j - 1])
		return (1);
	return (0);
}

void identify_envp_string(char **string, t_minishell *minishell)
{
	t_envp_list *iterator = minishell->list_envp;
	char *old_string = *string; // Conservez une copie de l'ancienne chaîne pour la libérer plus tard

	while (iterator != NULL)
	{
		if (ft_strncmp(*string, iterator->target, ft_strlen(iterator->target) - 2) == 0)
		{
			*string = ft_strdup(iterator->value);
			if (*string == NULL)
			{
				free(old_string); // Libérez l'ancienne chaîne en cas d'échec d'allocation
				exit_msg(minishell, "Malloc failed at identify_envp_string", -1);
			}
			if (check_equal_position_in_string(old_string, iterator))
			{
				char *temp = *string;
				*string = ft_strjoin(temp, "=");
				free(temp); // Libérez la chaîne temporaire utilisée pour la concaténation
				if (*string == NULL)
				{
					free(old_string); // Libérez l'ancienne chaîne en cas d'échec d'allocation
					exit_msg(minishell, "Malloc failed at identify_envp_string", -1);
				}
			}
			free(old_string); // Libérez l'ancienne chaîne maintenant que vous avez terminé avec elle
			break;
		}
		iterator = iterator->next;
	}
}


//void ignore_next_char(char *str, char c)
//{
//	char *char_to_ignore;
//	size_t len;
//
//	char_to_ignore = strchr(str, c);
//	if (char_to_ignore != NULL)
//	{
//		len = strlen(char_to_ignore);
//		ft_memmove(char_to_ignore, char_to_ignore + 1, len);
//		char_to_ignore[len - 1] = '\0';
//	}
//}

void ignore_dollar_string(char **string, t_minishell *minishell)
{
	char *new_string;
	size_t len;

	if (*string != NULL)
	{
		len = strlen(*string);
		new_string = malloc(len);
		if (new_string == NULL)
			exit_msg(minishell, "Malloc failed at ignore_dollar", -1);
		ft_memcpy(new_string, *string + 1, len);
		free(*string);
		*string = new_string;
	}
}

void expand_dollar_string(char **string, t_minishell *minishell)
{
	char *original_string = strdup(*string);
	if (original_string == NULL)
		exit_msg(minishell, "Malloc failed at expand_dollar_string", -1);
	ignore_dollar_string(string, minishell);
	identify_envp_string(string, minishell);
	if (strcmp(original_string, *string) != 0)
		free(original_string);
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
				previous_char = big[i + j - 1];
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
			expand_dollar_string(&iterator->name, minishell);
		iterator = iterator->next;
	}
}
