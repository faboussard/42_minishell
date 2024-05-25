/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "utils.h"
#include "parser.h"

void define_token_types(enum e_token_type type, enum e_token_builtin builtin, enum e_token_operators operator,
						t_token_list *token)
{
	token->e_type = type;
	token->e_builtin = builtin;
	token->e_operator = operator;
}

int define_token(t_token_list *new_token, char *string)
{
	new_token->name = ft_strdup(string);
	if (new_token->name == NULL)
		return (MALLOC_FAILED);
	new_token->next = NULL;
	new_token->is_quoted_delimiter = 0;
	if (get_operator_token(new_token, string) == FALSE)
		define_token_types(COMMAND, NO_BUILTIN, NO_OPERATOR, new_token);
	return (0);
}

void del_next_token(t_token_list **token)
{
	t_token_list *t2;
	t_token_list *t1;

	t1 = (*token);
	t2 = (*token)->next;
	t1->next = t2->next;
	free_token(t2);
}

t_token_list	*ft_lstlast_token(t_token_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void define_to_delete_tokens(t_token_list *const *list)
{
	(*list)->e_type = TO_DELETE;
	(*list)->next->e_type = TO_DELETE;
}