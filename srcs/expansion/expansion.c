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

int is_special_char(char c)
{
	if (c == '$' || c == '`' || c == '\\' || c == '=')
		return (1);
	return (0);
}

int check_special_char_after_expand(char *string, char *string2)
{
	int i;
	int j;

	i = 0;
	j = ft_strlen(string2);
	while (string[i] && string[i] != is_special_char(string2[j - 1]))
		i++;
	if (string[i] == string2[j])
		return (1);
	return (0);
}

char *expand_sign(char *string, char *temp)
{
	while (*string && *string != '=')
		string++;
	string = ft_strjoin(temp, string);
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


char *identify_envp_string(char *string, t_minishell *minishell)
{
	t_envp_list *iterator = minishell->list_envp;
	char *temp;

	while (iterator != NULL)
	{
		if (ft_strncmp(string, iterator->target, ft_strlen(iterator->target) - 1) == 0)
		{
			temp = ft_strdup(iterator->value);
			if (temp == NULL)
				exit_msg(minishell, "Malloc failed at identify_envp_string", -1);
			if (check_special_char_after_expand(string, iterator->target))
				string = expand_sign(string, temp);
			else
				string = ft_strdup(temp);
			if (temp)
			{
				free(temp);
				temp = NULL;
			}
			return (string);
		}
		iterator = iterator->next;
	}
	return (string);
}


char *expand_sigil(char *string, t_minishell *minishell)
{
	char *final_string;
	char *temp;
	int i;
	int j;

	i = 0;
	j = 0;
	temp = ft_calloc(1, ft_strlen(string) + 1);
	if (ft_isdigit(string[i]))
	{
		i++;
		while (string[i])
		{
			temp[j] = string[i];
			i++;
			j++;
		}
		final_string = ft_strdup(temp);
		free(temp);
	} else
		final_string = identify_envp_string(string, minishell);
	return (final_string);
}

void expander(t_minishell *minishell)
{
	t_token_list *iterator = minishell->list_tokens;

	while (iterator != NULL && iterator->next != NULL)
	{
		if (ft_strcmp(iterator->name, "$?") == 0)
		{
			printf("%d\n", minishell->status);
			return;
		}
		//////////// EVITER LES HEREDOC ///////////////////
		if (iterator->e_operator == HERE_DOC)
		{
			// Avancer au prochain token
			iterator = iterator->next;

			// Ignorer les espaces
			while (iterator && iterator->e_operator == IS_SPACE)
				iterator = iterator->next;

			// Rechercher le délimiteur du here document
			while (iterator && iterator->next && iterator->e_operator != IS_SPACE)
			{
				if (iterator->e_operator == DOUBLE_QUOTE || iterator->e_operator == SINGLE_QUOTE)
				{
					iterator = iterator->next;
					while (iterator && iterator->next && iterator->e_operator != DOUBLE_QUOTE && iterator->e_operator != SINGLE_QUOTE)
					iterator = iterator->next;
				}
				iterator = iterator->next;
			}
		}
////// EXPANSION ////////////////
	if (iterator->e_operator == DOLLAR && iterator->next->e_type != OPERATOR)
	{
		char *string = expand_sigil(iterator->next->name, minishell);
		if (string != iterator->next->name)
		{
			t_token_list *to_remove = iterator;
			iterator = iterator->next; // Avance iterator avant de supprimer le nœud actuel
			remove_node(&minishell->list_tokens, to_remove); // Supprime le nœud actuel
			free(iterator->name); // Libère la mémoire allouée pour le nom
			iterator->name = ft_strdup(string); // Remplace le nom par le nouveau string
			free(string); // Libère la mémoire allouée pour le nouveau string
			continue;
		}
		else
			del_next_token(&iterator); // Supprime le nœud suivant
	}
	iterator = iterator->next; // Avance l'itérateur pour passer au nœud suivant
}

}


