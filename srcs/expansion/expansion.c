/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/27 09:53:33 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "utils.h"

void	expand_tokens(t_minishell *m, t_token_list *it, int *squote_count,
		int *dquote_count)
{
	int	ignore_dquote;

	ignore_dquote = -1;
	while (it != NULL && it->next != NULL)
	{
		if (it->e_operator == HERE_DOC)
			handle_delimitor(&it);
		else if (it->e_operator == DOUBLE_QUOTE && (*dquote_count % 2 == 0)
			&& (*squote_count % 2 != 0))
			update_quote_counts(it, squote_count, &ignore_dquote);
		else if (it->e_operator == DOUBLE_QUOTE
			|| it->e_operator == SINGLE_QUOTE)
			update_quote_counts(it, squote_count, dquote_count);
		else if (it->e_operator == INPUT_REDIRECT
			|| it->e_operator == OUTPUT_REDIRECT
			|| it->e_operator == APPEND)
			handle_dollar_files(m, &it);
		else if (it->e_operator == DOLLAR && it->next != NULL)
			handle_dollar(m, &it, squote_count, dquote_count);
		if (it == NULL)
			break ;
		it = it->next;
	}
}

void	expand_for_heredoc(t_minishell *m, t_token_list *iterator,
		int *squote_count, int *dquote_count)
{
	while (iterator != NULL && iterator->next != NULL)
	{
		if (iterator->e_operator == DOLLAR && iterator->next != NULL)
		{
			if (is_redirect_token(iterator->next)
				&& iterator->next->next != NULL
				&& iterator->next->next->e_operator == IS_SPACE)
			{
				iterator->e_operator = 0;
				iterator = iterator->next;
				continue ;
			}
			process_dollar(m, &iterator, *squote_count, *dquote_count);
		}
		if (iterator == NULL)
			break ;
		iterator = iterator->next;
	}
}

void	expander(t_minishell *minishell, t_token_list **list, bool is_here_doc)
{
	t_token_list	*iterator;
	int				squote_count;
	int				dquote_count;

	squote_count = 0;
	dquote_count = 0;
	iterator = *list;
	if (is_here_doc)
		expand_for_heredoc(minishell, iterator, &squote_count, &dquote_count);
	else
		expand_tokens(minishell, iterator, &squote_count, &dquote_count);
}
