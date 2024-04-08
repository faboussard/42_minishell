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
	t_envp_list *iterator = minishell->list_envp;

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


void move_position_char(char *str, char c)
{
	char *char_to_ignore = strchr(str, c);
	if (char_to_ignore != NULL)
	{
		size_t len = strlen(char_to_ignore);
		memmove(char_to_ignore, char_to_ignore + 1, len); // Utilisation de memmove pour éviter les problèmes de chevauchement
		char_to_ignore[len - 1] = '\0'; // Mettre à jour la fin de la chaîne
	}
}

void ignore_equal_sign_envp(t_minishell *minishell)
{
	t_envp_list *iterator = minishell->list_envp;
	while (iterator != NULL)
	{
		move_position_char(iterator->target, '=');
		iterator = iterator->next;
	}
}

void ignore_dollar_token(t_token_list *token, t_minishell *minishell) {
	if (token->name != NULL)
	{
		size_t len = strlen(token->name);
		char *new_name = malloc(len); // Allouer de la mémoire pour la nouvelle chaîne
		if (new_name == NULL)
			exit_msg(minishell, "Malloc failed at ignore_dollar", -1);
		memcpy(new_name, token->name + 1, len); // Copier les caractères après le dollar
		free(token->name); // Libérer l'ancienne chaîne
		token->name = new_name;
	}
}

void expand_dollar_token(t_token_list *token, t_minishell *minishell) {
	// Sauvegarder la chaîne d'origine
	char *original_name = strdup(token->name);
	if (original_name == NULL)
		exit_msg(minishell, "Malloc failed at expand_dollar_token", -1);

	ignore_dollar_token(token, minishell);
	ignore_equal_sign_envp(minishell);
	identify_envp_token(token, minishell);

	// Libérer la mémoire de l'ancienne chaîne si elle a été modifiée
	if (strcmp(original_name, token->name) != 0) {
		free(original_name);
	}
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

void expand_and_create_envp_table(t_minishell *minishell) {
	t_token_list *iterator = minishell->list_tokens;
	while (iterator != NULL) {
		if (iterator->name[0] == '$' && iterator->name[1] != '\0' && ft_strnstr_and_check(minishell->user_input, iterator->name, ft_strlen(minishell->user_input)) == 0)
			expand_dollar_token(iterator, minishell);
		iterator = iterator->next;
	}
	create_envp_table(minishell);
}
