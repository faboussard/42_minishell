/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/11 17:01:49 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include "parser.h"

char	*ft_strjoin_free_s1(char *s1, char const *s2);
char	*ft_strjoin_free_s1_and_s2(char *s1, char *s2);
// int define_strlen_iterator_target(t_envp_list *iterator)
// {
// 	return (0);
// }

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

char *expand_equal_sign(char *string, char *temp)
{
	while (*string && *string != '=')
		string++;
	string = ft_strjoin_free_s1(temp, string);
	return (string);
}

char  *identify_envp_string(char *string, t_minishell *minishell)
{
	t_envp_list *iterator = minishell->list_envp;
	char *temp;

	while (iterator != NULL)
	{
		if (ft_strncmp(string, iterator->target, ft_strlen(iterator->target)) == 0)
		{
			temp = ft_strdup(iterator->value);
			if (temp == NULL)
				exit_msg(minishell, "Malloc failed at identify_envp_string", -1);
			if (check_equal_position_in_string(string, iterator->target))
				string = expand_equal_sign(string, temp);
			return (string);
		}
		iterator = iterator->next;
	}
	return (string);
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


char	*ft_strjoin_free_s1(char *s1, char const *s2)
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

char	*ft_strjoin_free_s1_and_s2(char  *s1, char *s2)
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
	free(s1);
	free(s2);
	new_string[i] = '\0';
	return (new_string);
}

char *add_until_char(char *temp,char *string, int *i, char c)
{
	int j;

	j = 0;
	while (string[*i] && (string[*i] != c || string[*i + 1] == '\0'))
		temp[j++] = string[(*i)++];
	if (j != 0)
		(*i)--;
	return (temp);
}


char *expand_sigil(char *string, t_minishell *minishell)
{
	int i;
	char *temp;
	char *sigil_string_to_check;
	char *final_string;
	char *expanded_sigil;

	final_string = NULL;
	final_string = ft_calloc(1, 1);
	i = 0;
	while (string[i])
	{
		temp = ft_calloc(1, ft_strlen(string) + 1);
		temp = add_until_char(temp, string, &i, '$');
		final_string = ft_strjoin_free_s1_and_s2(final_string, temp);
		if (string[i] == '$')
		{
			i++;
			sigil_string_to_check = add_until_char(temp, string, &i, '$');
			expanded_sigil = identify_envp_string(sigil_string_to_check, minishell);
			if (expanded_sigil != sigil_string_to_check)
				final_string = ft_strjoin_free_s1_and_s2(final_string, expanded_sigil);
			free(sigil_string_to_check);
		}
	}
	return (final_string);
}

void expander(t_minishell *minishell)
{
	t_token_list *iterator;
	char *string;

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
		{
			string = expand_sigil(iterator->name, minishell);
			size_t length = ft_strlen(string) + 1;
			ft_memmove(iterator->name, string, length);
			free(string);
		}

		iterator = iterator->next;
	}
}

//int ft_strnstr_and_check(const char *big, const char *little, size_t len)
//{
//	size_t i;
//	size_t j;
//	char previous_char;
//
//	i = 0;
//	while (big[i] != '\0')
//	{
//		j = 0;
//		while (big[i + j] == little[j] && ((i + j) < len))
//		{
//			j++;
//			if (j == 1)
//				previous_char = big[i + j - 1];
//			if (little[j] == '\0' && previous_char == '\'')
//				return (1);
//		}
//		i++;
//	}
//	return (0);
//}

