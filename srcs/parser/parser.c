/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/19 11:06:17 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "utils.h"
#include <stdlib.h>

// ETAPES
// 1. TOUT TOKENIZER	: CHAQUE TOKEN EST UN OPERATEUR(ESPACE GUILLEMT PIPE AUTRE) OU UN MOT. les dollqrs et quillemets sont separes des mots.
// 2. EXPAND ( SI TOKEN DOLLAR : ON ANALYSE LE TOKEN SUIVANT). donc si guillements : expansion non faite
// 3. JOIN CE QUIL Y A ENTRE QUOTES SANS LES QUOTES
// 4. ENLEVER LES TOKEN SINGLESQUOTES S ILS NE SONT PAS PRECEDES OU SUIVIS DE TOKEN DQUOTES
// JOINDRE LES TOKEN SINGLE QUOTES RESTQNTES A LEUR MOTS
// 3. ENLEVER LES TOKENS DQUOTES
// 4. ENLEVER LES TOKENS ESPACES
// ATTENTION : regarder si = ou digits ( variables envp valable !)

void	arg_to_command(t_token_list *list_tokens)
{
	t_token_list	*iterator;
	t_token_list	*next_token;

	iterator = list_tokens;
	if (ft_lstsize_token(iterator) == 1)
		iterator->e_type = COMMAND;
	else
	{
		while (iterator->next != NULL)
		{
			next_token = iterator->next;
			if (iterator->e_type == COMMAND && next_token->e_type != OPERATOR
				&& next_token->e_type != IN_FILE
				&& next_token->e_type != OUT_FILE)
				next_token->e_type = ARGUMENT;
			if (iterator->e_operator == DOLLAR)
				iterator->e_type = COMMAND;
			if (iterator->e_type == ARGUMENT && next_token->e_type != OPERATOR)
				next_token->e_type = ARGUMENT;
			iterator = iterator->next;
		}
	}
}

void	to_infile_or_outfile(t_token_list *list_tokens)
{
	t_token_list	*iterator;
	t_token_list	*next_token;

	iterator = list_tokens;
	while (iterator && iterator->next != NULL)
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

void	token_requalification(t_token_list *list_tokens)
{
	if (list_tokens)
	{
		to_infile_or_outfile(list_tokens);
		arg_to_command(list_tokens);
	}
}

// void check_sequence_dollar_followed_by_quotes(char *user_input)
//{
//	size_t	i;
//	i = 0;
//
//	while (user_input[i + 1] != '\0')
//	{
//		if (user_input[i] == '$' && user_input[i + 1] == '\"')
//		{
//			ft_memcpy(&user_input[i], &user_input[i + 1], ft_strlen(user_input
//					- 1));
//		}
//		i++;
//	}
//}

// void remove_single_quotes(t_minishell *minishell, t_token_list **list)
//{
//	t_token_list *cpy;
//
//	cpy = (*list);
//	while ((*list)->next != NULL)
//	{
//		if ((*list)->next->e_operator == SINGLE_QUOTE
//			&& (*list)->e_operator == DOUBLE_QUOTE)
//			(*list) = (*list)->next;
//		if ((*list)->next->next != NULL &&
//			(((*list)->next->e_operator == SINGLE_QUOTE
//					&& (*list)->next->next->e_operator != DOUBLE_QUOTE) ||
//				((*list)->next->e_operator == DOUBLE_QUOTE
//					&& (*list)->e_operator != SINGLE_QUOTE) ||
//				((*list)->next->e_operator == SINGLE_QUOTE
//					&& (*list)->next->next == NULL)))
//			del_next_token(&minishell->list_tokens);
//		else
//			(*list) = (*list)->next;
//	}
//	*list = cpy;
//}

int	cmp(int op1, int op2)
{
	return (op1 - op2);
}

void remove_empty_between_words(t_token_list **list)
{
	t_token_list *cpy;

	cpy = *list;
	while (*list != NULL && (*list)->next != NULL)
	{
		if (strcmp((*list)->name, "\0") == 0 && (*list)->next->e_type == COMMAND)
			(*list)->e_operator = DOUBLE_QUOTE;
		if (strcmp((*list)->next->name, "\0") == 0 && (*list)->e_type == COMMAND)
			(*list)->next->e_operator = DOUBLE_QUOTE;
		*list = (*list)->next;
	}
	*list = cpy;
}


// int is_only_squote(char *str)
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
//		if (count == ft_strlen(str) - 2)
// Vérifier si count est égal à la longueur de la chaîne - 2
//			return (1);
//	}
//	return (0);
//}

// int is_only_dquote(char *str)
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

void join_quotes_between_spaces(t_minishell *minishell, t_token_list **list);

int count_if_only_quotes_in_all_list(t_minishell *minishell, t_token_list **list)
{
	int size_list;
	int count_double_quote;
	int count_single_quote;

	size_list = ft_lstsize_token(*list);
	count_double_quote = count_token_by_operator(minishell, DOUBLE_QUOTE);
	count_single_quote = count_token_by_operator(minishell, SINGLE_QUOTE);
	if (count_double_quote == size_list || count_single_quote == size_list)
		return 1;
	else
		return 0;
}

//void replace_tokens_with_only_quotes_by_null(t_minishell *minishell, t_token_list **list)
//{
//	t_token_list *cpy;
//	t_token_list *mutex;
//
//	cpy = *list;
//	while (*list != NULL && (*list)->next != NULL)
//	{
//		if (iterator_is_only_quotes(*list))
//	}
//}

void define_heredoc_and_append(t_minishell *minishell, t_token_list **list)
{
	t_token_list *cpy;

	cpy = *list;
	while (*list != NULL && (*list)->next != NULL)
	{
		if ((*list)->e_operator == INPUT_REDIRECT && (*list)->next->e_operator == INPUT_REDIRECT)
		{
			join_tokens(minishell, list);
			(*list)->e_type = OPERATOR;
			(*list)->e_operator = HERE_DOC;
		}
		if ((*list)->e_operator == OUTPUT_REDIRECT && (*list)->next->e_operator == OUTPUT_REDIRECT)
		{
			join_tokens(minishell, list);
			(*list)->e_type = OPERATOR;
			(*list)->e_operator = APPEND;
		}
		*list = (*list)->next;
	}
	*list = cpy;
}

void supress_two_consecutive_empty_names(t_minishell *minishell, t_token_list **list)
{
	t_token_list *cpy;

	cpy = *list;
	while (*list != NULL && (*list)->next != NULL)
	{
		if (strcmp((*list)->name, "\0") == 0 && strcmp((*list)->next->name, "\0") == 0)
		{
			join_tokens(minishell, list);
			continue;
		}
		*list = (*list)->next;
	}
	*list = cpy;
}


int	parse_input(t_minishell *minishell)
{
	char	*string;
// passer les espaces inutiles.
//des uqon crois eun uote, on prend lindex de lautre
	//utiliser ft_strchr pour trouver la prochaine quote
	//utiliser is_space
	//utiliser ft_substr
	//remove quotes avant de join les espaces..
	//pas dejoin entre quotes !!!!!!
	string = minishell->user_input;
	transform_to_token(minishell, string);
	define_heredoc_and_append(minishell, &minishell->list_tokens);
	if (check_syntax(minishell) == 1)
	{
		minishell->status = set_or_get_last_status(2, 0);
		return (1);
	}
	//	supress_double_quotes(&minishell->list_tokens);
	// pas possible car : "''"
	//	rename_dollar_token_between_dquote(&minishell->list_tokens);
	// bash pratique lexpansion des
	//	rename_last_dollar(&minishell->list_tokens);
	//	join_single_quote_and_dollar(minishell, &minishell->list_tokens);
	expander(minishell);
	// bash pratique lexpansion des variable en excluant les variables entre quote. il supprime les autres dollars.
	//	join_if_between_quotes(minishell, &minishell->list_tokens); // pas necessaire on enleve le dollar uniquement pendant lexpansion
	join_between_quotes(minishell, &minishell->list_tokens);
	supress_two_consecutive_empty_names(minishell, &minishell->list_tokens);
	remove_empty_between_words( &minishell->list_tokens);
	ft_list_remove_if(&minishell->list_tokens, (void *)SINGLE_QUOTE, cmp);
	ft_list_remove_if(&minishell->list_tokens, (void *)DOUBLE_QUOTE, cmp);
	join_between_spaces(minishell, &minishell->list_tokens);
//	replace_tokens_with_only_quotes_by_null(minishell);
	ft_list_remove_if(&minishell->list_tokens, (void *)IS_SPACE, cmp);
	token_requalification(minishell->list_tokens);
	create_envp_table(minishell);
	create_process_list(minishell);
	return (0);
}
