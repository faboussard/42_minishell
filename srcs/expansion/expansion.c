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

//void ignore_dollar_string(char **string, t_minishell *minishell)
//{
//	char *new_string;
//	size_t len;
//
//	if (*string != NULL)
//	{
//		len = strlen(*string);
//		new_string = malloc(len); // La longueur est len - 1
//		if (new_string == NULL)
//			exit_msg(minishell, "Malloc failed at ignore_dollar", -1);
//		ft_memmove(new_string, *string + 1, len - 1); // Utilisation de len - 1 pour la longueur
//		free(*string);
//		*string = new_string;
//	}
//}

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
	if (temp == NULL)
		exit_msg(minishell, "Malloc failed at expand_sigil", -1);
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
	} else
		final_string = identify_envp_string(string, minishell);
	free(temp);
	return (final_string);
}

void change_name_to_status(t_minishell *minishell, t_token_list *iterator)
{
	join_tokens(minishell, &iterator);
	free(iterator->name);
	iterator->name = ft_itoa(minishell->status);
	if (iterator->name == NULL)
		exit_msg(minishell, "Malloc failed at expander", -1);
}

//void handle_quotes_before_expansion(t_token_list *iterator, t_minishell *minishell, int s_count, int d_count)
//{
//	if (iterator->next->e_operator == SINGLE_QUOTE)
//	{
//		if (s_count % 2 != 0 && s_count != 0)
//		{
//			t_token_list *to_remove = iterator;
//			iterator = iterator->next;
//			remove_node(&minishell->list_tokens, to_remove);
//		}
//	}
//	else if (iterator->next->e_operator == DOUBLE_QUOTE)
//	{
//		if (d_count % 2 != 0 && d_count != 0)
//		{
//			t_token_list *to_remove = iterator;
//			iterator = iterator->next;
//			remove_node(&minishell->list_tokens, to_remove);
//		}
//	}
//}

void expander(t_minishell *minishell)
{

	t_token_list *iterator;
	iterator = minishell->list_tokens;
	int d_count;
	int s_count;

	s_count = 0;
	d_count = 0;
	while (iterator != NULL && iterator->next != NULL)
	{
		if (iterator->e_operator == HERE_DOC)
			handle_delimitor(iterator);
		if (iterator->e_operator == DOUBLE_QUOTE || iterator->e_operator == SINGLE_QUOTE)
			add_quote_count(iterator, &s_count, &d_count);
		else if (iterator->e_operator == DOLLAR)
		{
			if (ft_strncmp(iterator->next->name, "?", 2) == 0) 		//mettre ici lexpanion du shelllevel ?
				change_name_to_status(minishell, iterator);
			else if (iterator->e_operator == DOUBLE_QUOTE || iterator->e_operator == SINGLE_QUOTE)
				add_quote_count(iterator->next, &s_count, &d_count);
			else if (s_count % 2 == 0)
			{
				char *string = expand_sigil(iterator->next->name, minishell);
				if (string != iterator->next->name)
				{
					t_token_list *to_remove = iterator;
					iterator = iterator->next;
					remove_node(&minishell->list_tokens, to_remove);
					free(iterator->name);
					iterator->name = ft_strdup(string);
					free(string);
					continue;
				}
				else
					del_next_token(&iterator);
			}
		}
		iterator = iterator->next;
	}
}


