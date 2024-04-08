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
			token->name = ft_strdup(iterator->value);
			if (token->name == NULL)
				exit_msg(minishell, "Malloc failed at identify_envp_token", -1);
		}
		iterator = iterator->next;
	}
}

void move_position_char(char *str, char c)
{
	char *char_to_ignore = strchr(str, c);
	if (char_to_ignore != NULL)
		ft_memmove(char_to_ignore, char_to_ignore + 1, strlen(char_to_ignore));
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

void ignore_dollar_token(t_token_list *token, t_minishell *minishell)
{
	if (token->name != NULL) {
		size_t len = ft_strlen(token->name); // Longueur de la sous-chaîne à copier
		token->name = ft_memmove(token->name, token->name + 1, len); // Déplacer la sous-chaîne vers le début de la chaîne
		token->name[len] = '\0'; // Terminer la chaîne correctement
	}
	if (token->name == NULL)
		exit_msg(minishell, "Malloc failed at ignore_dollar", -1);
}

void expand_dollar_token(t_token_list *token, t_minishell *minishell)
{
	ignore_dollar_token(token, minishell);
	ignore_equal_sign_envp(minishell);
	identify_envp_token(token, minishell);
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

void expand_and_create_envp_table(t_minishell *minishell)
{
	t_token_list *iterator;



	iterator = minishell->list_tokens;
	while (iterator != NULL)
	{
//		if (iterator->name[0] == '$' && iterator->name[1] == '\0')
//			//do something;
		if (iterator->name[0] == '$' && iterator->name[1] != '\0' && ft_strnstr_and_check(minishell->user_input, iterator->name, ft_strlen(minishell->user_input)) == 0)
			expand_dollar_token(iterator, minishell);
		iterator = iterator->next;
//		else if (ft_strcmp(iterator->name, "$?") == 0)
//			expand_question_mark_token(iterator, minishell);
	}
	create_envp_table(minishell);
}
