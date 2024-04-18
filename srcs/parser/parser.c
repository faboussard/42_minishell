/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                            :+:      :+:    :+:  */
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
#include <stdlib.h>

//ETAPES
//1. TOUT TOKENIZER	: CHAQUE TOKEN EST UN OPERATEUR(ESPACE GUILLEMT PIPE AUTRE) OU UN MOT. les dollqrs et quillemets sont separes des mots.
//2. EXPAND ( SI TOKEN DOLLAR : ON ANALYSE LE TOKEN SUIVANT). donc si guillements : expansion non faite
// 3. JOIN CE QUIL Y A ENTRE QUOTES SANS LES QUOTES
// 4. ENLEVER LES TOKEN SINGLESQUOTES S ILS NE SONT PAS PRECEDES OU SUIVIS DE TOKEN DQUOTES
// JOINDRE LES TOKEN SINGLE QUOTES RESTQNTES A LEUR MOTS
//3. ENLEVER LES TOKENS DQUOTES
//4. ENLEVER LES TOKENS ESPACES
// ATTENTION : regarder si = ou digits ( variables envp valable !)

void arg_to_command(t_token_list *list_tokens)
{
	t_token_list *iterator;
	t_token_list *next_token;

	iterator = list_tokens;
	if (ft_lstsize_token(iterator) == 1)
	{
		if (iterator->e_type == ARGUMENT)
			iterator->e_type = COMMAND;
	} else
	{
		while (iterator->next != NULL)
		{
			next_token = iterator->next;
			if (iterator->e_type == COMMAND && next_token->e_type != OPERATOR && next_token->e_type != IN_FILE &&
				next_token->e_type != OUT_FILE)
				next_token->e_type = ARGUMENT;
			if (iterator->e_operator == DOLLAR)
				iterator->e_type = COMMAND;
			iterator = iterator->next;
		}
	}
}

void to_infile_or_outfile(t_token_list *list_tokens)
{
	t_token_list *iterator;
	t_token_list *next_token;

	iterator = list_tokens;
	while (iterator->next != NULL)
	{
		next_token = iterator->next;
		if (iterator->e_operator == INPUT_REDIRECT)
			next_token->e_type = IN_FILE;
		if (iterator->e_operator == OUTPUT_REDIRECT)
			next_token->e_type = OUT_FILE;
		if (iterator->e_operator == HERE_DOC)
			next_token->e_type = DELIMITER;
		if (iterator->e_operator == APPEND)
			next_token->e_type = APPEND_FILE;
		iterator = iterator->next;
	}
}

void token_requalification(t_token_list *list_tokens)
{
	to_infile_or_outfile(list_tokens);
	arg_to_command(list_tokens);
}

//void check_sequence_dollar_followed_by_quotes(char *user_input)
//{
//	size_t	i;
//	i = 0;
//
//	while (user_input[i + 1] != '\0')
//	{
//		if (user_input[i] == '$' && user_input[i + 1] == '\"')
//		{
//			ft_memcpy(&user_input[i], &user_input[i + 1], ft_strlen(user_input - 1));
//		}
//		i++;
//	}
//}


//void remove_single_quotes(t_minishell *minishell, t_token_list **list)
//{
//	t_token_list *cpy;
//
//	cpy = (*list);
//	while ((*list)->next != NULL)
//	{
//		if ((*list)->next->e_operator == SINGLE_QUOTE && (*list)->e_operator == DOUBLE_QUOTE)
//			(*list) = (*list)->next;
//		if ((*list)->next->next != NULL &&
//			(((*list)->next->e_operator == SINGLE_QUOTE && (*list)->next->next->e_operator != DOUBLE_QUOTE) ||
//			 ((*list)->next->e_operator == DOUBLE_QUOTE && (*list)->e_operator != SINGLE_QUOTE) ||
//			 ((*list)->next->e_operator == SINGLE_QUOTE && (*list)->next->next == NULL)))
//			del_next_token(&minishell->list_tokens);
//		else
//			(*list) = (*list)->next;
//	}
//	*list = cpy;
//}

int cmp(int op1, int op2)
{
	return (op1 - op2);
}


//int is_only_squote(char *str)
//{
//	int i;
//	int count;
//
//	i = 0;
//	count = 0;
//	if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
//	{
//		i++;
//		while (str[i])
//		{
//			if (str[i] == '\'')
//				count++;
//			i++; // Incrémenter i à chaque itération
//		}
//		if (count == ft_strlen(str) - 2) // Vérifier si count est égal à la longueur de la chaîne - 2
//			return (1);
//	}
//	return (0);
//}


//int is_only_dquote(char *str)
//{
//	int i;
//
//	i = 0;
//	if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
//	{
//		while (*str)
//		{
//			if (str[i] == '\'')
//				i++;
//		}
//		if (i == ft_strlen(str) - 1)
//			return (1);
//	}
//	return (0);
//}

void delete_dollar_before_join(t_token_list **list);
void supress_double_quotes(t_token_list **list);

int parse_input(t_minishell *minishell)
{
	char *string;

	string = minishell->user_input;
	transform_to_token(minishell, string);
	if (check_syntax(minishell) == 1)
		return (1);
//	supress_double_quotes(&minishell->list_tokens); // pas possible car : "''"
//	rename_dollar_token_between_dquote(&minishell->list_tokens); // bash pratique lexpansion des
//	rename_last_dollar(&minishell->list_tokens);
//	join_dollar_and_single_quote(minishell, &minishell->list_tokens);
	expander(minishell); // bash pratique lexpansion des variable en excluant les variables entre quote. il supprime les autres dollars. 
//	join_if_between_quotes(minishell, &minishell->list_tokens); // pas necessaire, on enleve le dollar uniquement pendant lexpansion 
	join_between_quotes(minishell, &minishell->list_tokens);
	ft_list_remove_if(&minishell->list_tokens, (void *) SINGLE_QUOTE, cmp);
	ft_list_remove_if(&minishell->list_tokens, (void *) DOUBLE_QUOTE, cmp);
	join_between_spaces(minishell, &minishell->list_tokens);
	ft_list_remove_if(&minishell->list_tokens, (void *) IS_SPACE, cmp);
	token_requalification(minishell->list_tokens);
	create_envp_table(minishell);
	create_process_list(minishell);
	return (0);
}
