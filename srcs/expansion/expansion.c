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

char	*ft_strjoin_free_s1(char const *s1, char const *s2);
char	*ft_strjoin_free_s1_and_s2(char const *s1, char const *s2);

int check_equal_position_in_string(char *string, char *string2)
{
	int i;
	int j;

	i = 0;
	j = ft_strlen(string2);
	while (string[i] && string[i] != '=')
		i++;
	if (string[i] == string2[j - 1])
		return (1);
	return (0);
}

char  *identify_envp_string(char *string, t_minishell *minishell)
{
	t_envp_list *iterator = minishell->list_envp;
	char *old_string = string;
	char *temp;

	while (iterator != NULL)
	{
		if (ft_strncmp(string, iterator->target, ft_strlen(iterator->target)) == 0)
		{
			temp = ft_strdup(iterator->value); // Allouez une nouvelle chaîne pour la valeur de l'environnement
			if (temp == NULL)
				exit_msg(minishell, "Malloc failed at identify_envp_string", -1);
			if (check_equal_position_in_string(old_string, iterator->target))
				string = ft_strjoin(temp, "=");
			free(temp);
			// temp est free dans tous les cas : si il a ete str join ou si il ne la pas ete
			return (string);
		}
		iterator = iterator->next;
	}
	return (old_string);
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
		new_string = malloc(len); // La longueur est len - 1
		if (new_string == NULL)
			exit_msg(minishell, "Malloc failed at ignore_dollar", -1);
		ft_memmove(new_string, *string + 1, len - 1); // Utilisation de len - 1 pour la longueur
		free(*string);
		*string = new_string;
	}
}


char	*ft_strjoin_free_s1(char const *s1, char const *s2)
{
	char	*new_string;
	size_t	i;
	size_t	j;
	size_t	total_length;

	total_length = ft_strlen(s1) + ft_strlen(s2);
	new_string = malloc(sizeof(char) * total_length + 1);
	if (new_string == NULL)
		return (0);
	i = 0;
	while (i < ft_strlen(s1))
	{
		new_string[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
	{
		new_string[i] = s2[j];
		j++;
		i++;
	}
	free((void*)s1);
	new_string[i] = '\0';
	return (new_string);
}

char	*ft_strjoin_free_s1_and_s2(char const *s1, char const *s2)
{
	char	*new_string;
	size_t	i;
	size_t	j;
	size_t	total_length;

	total_length = ft_strlen(s1) + ft_strlen(s2);
	new_string = malloc(sizeof(char) * total_length + 1);
	if (new_string == NULL)
		return (0);
	i = 0;
	while (i < ft_strlen(s1))
	{
		new_string[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
	{
		new_string[i] = s2[j];
		j++;
		i++;
	}
	free((void*)s1);
	new_string[i] = '\0';
	return (new_string);
}

void expand_dollar_string(char **string, t_minishell *minishell)
{
	int i;
	int j;
	int k;
	char *cpy_string;
	char *temp;
	char *return_string;

	cpy_string = *string;
	return_string = ft_calloc(1, ft_strlen(cpy_string) + 1);
	i = 0;
	k = 0;
	while (cpy_string[i])
	{
		while (cpy_string[i] && (cpy_string[i] != '$' || cpy_string[i + 1] == '\0'))
			return_string[k++] = cpy_string[i++];
		if (cpy_string[i] == '$')
		{
			i++;
			temp = ft_calloc(1, ft_strlen(cpy_string) + 1);
			j = 0;
			while (cpy_string[i] && cpy_string[i] != '$')
				temp[j++] = cpy_string[i++];
			char *temp2 = identify_envp_string(temp, minishell);
			if (temp2 != temp)
				return_string = ft_strjoin_free_s1(return_string, temp2);
			free(temp);
		}
	}
	if (return_string)
	{
		free(*string);
		*string = return_string;
		free(return_string);
	}
}


int ft_strnstr_and_check(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;
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
			&& ft_strchr(iterator->name, '$') != NULL
			&& ft_strnstr(iterator->name, "$'", 2) == NULL
//			&& ft_strnstr_and_check(minishell->user_input, iterator->name, ft_strlen(minishell->user_input)) == 0
				)
			//ajoter contiion ca menleve une lettre
			expand_dollar_string(&iterator->name, minishell);
		iterator = iterator->next;
	}
}
