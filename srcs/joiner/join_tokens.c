/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/02 09:50:06 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "utils.h"
#include <stdlib.h>

static int	skip_op(t_token_list **list, int count)
{
	{
		define_token_types(COMMAND, NO_BUILTIN, NO_OPERATOR, (*list));
		(*list) = (*list)->next;
		(*list) = (*list)->next;
		count++;
	}
	return (count);
}

void	join_between_quotes_handler(t_token_list **list,
		enum e_token_operators op, t_minishell *m)
{
	int				count;
	t_token_list	*cpy;

	count = 1;
	cpy = *list;
	if (*list == NULL || (*list)->next == NULL || (*list)->next->next == NULL)
		return ;
	(*list) = (*list)->next;
	while ((*list) && (*list)->next)
	{
		if ((*list)->next->e_operator == op)
			count = skip_op(list, count);
		if (count == 2)
			return ;
		else if (count == 1)
			join_tokens_safely(m, list, cpy);
	}
}

void	join_between_quotes(t_minishell *m, t_token_list **list)
{
	t_token_list	*cpy;
	int				quote_type;

	cpy = *list;
	while (*list != NULL && (*list)->next != NULL)
	{
		quote_type = (*list)->e_operator;
		if ((quote_type == DOUBLE_QUOTE || quote_type == SINGLE_QUOTE)
			&& quote_type == (int)(*list)->next->e_operator)
		{
			join_tokens_safely(m, list, cpy);
			change_token_name(list, "\0");
			continue ;
		}
		else if ((quote_type == DOUBLE_QUOTE || quote_type == SINGLE_QUOTE)
				&& check_if_more_tokens(list, quote_type))
		{
			join_between_quotes_handler(list, quote_type, m);
			if ((*list) == NULL)
				break ;
		}
		else
			(*list) = (*list)->next;
	}
	*list = cpy;
}

void	join_between_spaces(t_minishell *minishell, t_token_list **list)
{
	t_token_list	*cpy;

	cpy = *list;
	do_join_not_spaces(minishell, list);
	*list = cpy;
}

char *join_in_heredoc(t_token_list **list)
{
	t_token_list	*iterator;
	char			*new_name;
	char			*temp;

	new_name = NULL;
	if (list == NULL)
		return (NULL);
	iterator = *list;
	temp = ft_calloc(1, sizeof(char));
	if (temp == NULL)
		return (NULL);
	while (iterator)
	{
		new_name = ft_strjoin(temp, iterator->name);
		free_safely_str(&temp);
		if (new_name == NULL)
			return (NULL);
		temp = new_name;
		iterator = iterator->next;
	}
	return (new_name);
}
