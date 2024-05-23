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

void ft_lsti_insert_after(t_token_list **current, t_token_list *new_token)
{
	if (current == NULL || *current == NULL || new_token == NULL)
		return;
	new_token->next = (*current)->next;
	(*current)->next = new_token;
}


void create_and_insert_token(t_minishell *minishell, char *string, t_token_list **current)
{
	t_token_list *new_token;

	new_token = ft_calloc(1, sizeof(t_token_list));
	if (new_token == NULL)
	{
		free_safely_str(&string);
		exit_msg(minishell, "Malloc failed at create_token", ENOMEM);
	}
	if (define_token(new_token, string) == 0)
	{
		free_safely_str(&string);
		free(new_token);
		exit_msg(minishell, "Failed to define token at create_token", ENOMEM);
	}
	ft_lsti_insert_after(current, new_token);
}


void add_tokens_and_change_to_expansion(t_minishell *m, t_token_list **list, char *expanded_string)
{
	char **split;
	int i;
	t_token_list *current;

	i = 0;
	split = ft_split(expanded_string, ' ');
	if (split == NULL)
		exit_msg(m, "Malloc failed at add_tokens_and_change_to_expansion", ENOMEM);

	current = *list;
	while (split[i])
	{
		create_and_insert_token(m, split[i], &current);
		current = current->next; // Move to the newly added token
		i++;
	}
	free_safely_str(&expanded_string);
	ft_free_tab(&split);
}
void process_dollar_token(t_minishell *m, t_token_list **list, int squote_count, int dquote_count)
{
	char *expanded_string;

	if (ft_strncmp((*list)->next->name, "?", 2) == 0)
		change_name_to_status(m, *list);
	else
	{
		if (squote_count % 2 != 0 && dquote_count % 2 == 0)
			return ;
		if (!ft_isalnum((*list)->next->name[0]) && (*list)->next->name[0] != '_' && dquote_count % 2 == 0)
			(*list)->e_operator = 0;
		else
		{
			define_to_delete_tokens(list);
			expanded_string = expand_sigil((*list)->next->name, m);
			if (expanded_string != (*list)->next->name)
			{
				if (ft_strchr(expanded_string, ' ') != NULL)
					add_tokens_and_change_to_expansion(m, list, expanded_string);
				else
					change_to_expansion(m, list, &expanded_string);
				return;
			}
			else
				define_to_delete_tokens(list);
		}
	}
}

void handle_dollar_files(t_minishell *m, t_token_list **list)
{
	char *expanded_string;

	expanded_string = NULL;
	(*list) = (*list)->next;
	if ((*list)->next == NULL)
		return;
	while ((*list) && (*list)->e_operator == IS_SPACE)
		(*list) = (*list)->next;
	if (*list && (*list)->e_operator == DOLLAR)
	{
		expanded_string = expand_sigil((*list)->next->name, m);
		if (expanded_string != (*list)->next->name)
		{
			change_to_expansion(m, list, &expanded_string);
			return ;
		}
		else
			(*list)->failed_expand = true;
	}
}

void handle_dollar(t_minishell *m, t_token_list **iterator, int *squote_count, int *dquote_count)
{
	if ((*iterator)->next == NULL)
		return ;
	if ((is_redirect_token((*iterator)->next) && (*iterator)->next->next != NULL
		&& (*iterator)->next->next->e_operator == IS_SPACE)
	    || s_quote_after_d_quote_and_dollar(iterator, *squote_count, *dquote_count))
	{
		*iterator = (*iterator)->next;
		return ;
	}
	if ((*iterator)->next->e_operator == SINGLE_QUOTE && (*squote_count % 2 == 0) && (*dquote_count % 2 == 0))
	{
		define_to_delete_tokens(iterator);
		*iterator = (*iterator)->next;
		return ;
	}
	add_quotes_count(*iterator, squote_count, dquote_count);
	process_dollar_token(m, iterator, *squote_count, *dquote_count);
}

void expand_tokens(t_minishell *m, t_token_list *iterator, int *squote_count, int *dquote_count)
{
	int ignore_dquote;

	ignore_dquote= -1;
	while (iterator != NULL && iterator->next != NULL)
	{
		if (iterator->e_operator == HERE_DOC)
			handle_delimitor(&iterator);
		else if (iterator->e_operator == DOUBLE_QUOTE && (*dquote_count % 2 == 0) && (*squote_count % 2 != 0))
			update_quote_counts(iterator, squote_count, &ignore_dquote);
		else if (iterator->e_operator == DOUBLE_QUOTE || iterator->e_operator == SINGLE_QUOTE)
			update_quote_counts(iterator, squote_count, dquote_count);
		else if (iterator->e_operator == INPUT_REDIRECT || iterator->e_operator == OUTPUT_REDIRECT
		|| iterator->e_operator == APPEND)
			handle_dollar_files(m, &iterator);
		else if (iterator->e_operator == DOLLAR && iterator->next != NULL)
			handle_dollar(m, &iterator, squote_count, dquote_count);
		if (iterator == NULL)
			break ;
		iterator = iterator->next;
	}
}

void expand_for_heredoc(t_minishell *m, t_token_list *iterator, int *squote_count, int *dquote_count)
{
	while (iterator != NULL && iterator->next != NULL)
	{
		if (iterator->e_operator == DOLLAR && iterator->next != NULL)
		{
			if (is_redirect_token(iterator->next) && iterator->next->next != NULL &&
				iterator->next->next->e_operator == IS_SPACE)
			{
				iterator->e_operator = 0;
				iterator = iterator->next;
				continue;
			}
			process_dollar_token(m, &iterator, *squote_count, *dquote_count);
		}
		if (iterator == NULL)
			break ;
		iterator = iterator->next;
	}
}


void expander(t_minishell *minishell, t_token_list **list, bool is_here_doc)
{
	t_token_list *iterator;
	int squote_count;
	int dquote_count;

	squote_count = 0;
	dquote_count = 0;
	iterator = *list;
	if (is_here_doc)
		expand_for_heredoc(minishell, iterator, &squote_count, &dquote_count);
	else
		expand_tokens(minishell, iterator, &squote_count, &dquote_count);
}
