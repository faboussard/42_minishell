/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/27 10:15:51 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "utils.h"

void	process_expand(t_minishell *m, t_token_list **list, char **exp_string)
{
	if (ft_strchr((*exp_string), ' ') != NULL)
		split_and_expand(m, list, *exp_string);
	else
		change_to_expansion(m, list, exp_string);
	free_safely_str(exp_string);
}

void	process_dollar(t_minishell *m, t_token_list **list,
		int squote_count, int dquote_count)
{
	char	*exp_string;

	exp_string = NULL;
	if (ft_strncmp((*list)->next->name, "?", 2) == 0)
		change_to_status(m, *list);
	else
	{
		if (squote_count % 2 != 0 && dquote_count % 2 == 0)
			return ;
		if (!ft_isalnum((*list)->next->name[0]) && (*list)->next->name[0] != '_'
			&& dquote_count % 2 == 0)
			(*list)->e_operator = 0;
		else
		{
			define_to_delete_tokens(list);
			exp_string = expand_sigil((*list)->next->name, m);
			if (exp_string != (*list)->next->name)
			{
				process_expand(m, list, &exp_string);
				return ;
			}
			else
				define_to_delete_tokens(list);
		}
	}
}

void	handle_dollar_files(t_minishell *m, t_token_list **list)
{
	char	*expanded_string;

	expanded_string = NULL;
	(*list) = (*list)->next;
	if ((*list)->next == NULL)
		return ;
	while ((*list) && (*list)->e_operator == IS_SPACE)
		(*list) = (*list)->next;
	if (*list && (*list)->e_operator == DOLLAR)
	{
		expanded_string = expand_sigil((*list)->next->name, m);
		if (expanded_string != (*list)->next->name)
		{
			change_to_expansion(m, list, &expanded_string);
			free_safely_str(&expanded_string);
			return ;
		}
		else
			(*list)->failed_expand = true;
	}
}

void	handle_dollar(t_minishell *m, t_token_list **iterator,
		int *squote_count, int *dquote_count)
{
	if ((*iterator)->next == NULL)
		return ;
	if ((is_redirect_token((*iterator)->next) && (*iterator)->next->next != NULL
			&& (*iterator)->next->next->e_operator == IS_SPACE)
		|| s_quote_after_d_quote_and_dollar(iterator, *squote_count,
			*dquote_count))
	{
		*iterator = (*iterator)->next;
		return ;
	}
	if ((*iterator)->next->e_operator == SINGLE_QUOTE && (*squote_count
			% 2 == 0) && (*dquote_count % 2 == 0))
	{
		define_to_delete_tokens(iterator);
		*iterator = (*iterator)->next;
		return ;
	}
	add_quotes_count(*iterator, squote_count, dquote_count);
	process_dollar(m, iterator, *squote_count, *dquote_count);
}
