/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/18 10:34:38 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdlib.h>
#include "parser.h"

char find_sep(char c)
{
	if (c == ' ' || c == '\t')
		return (' ');
	if (c == '\'')
		return ('\'');
	if (c == '\"')
		return ('\"');
	if (c == '$')
		return ('\"');
	return (0);
}

void join_tokens(t_minishell *minishell, t_token_list **list)
{
	char *joined_name;
	t_token_list *t2;
	t_token_list *t1;

	t1 = (*list);
	t2 = (*list)->next;
	joined_name = ft_strjoin(t1->name, t2->name);
	free(t1->name);
	t1->name = ft_strdup(joined_name);
	free(joined_name);
	if (t1->name == NULL)
		exit_msg(minishell, "Malloc failed at tokenization", 1);
	del_next_token(&t1);
	define_token_types(COMMAND, NO_BUILTIN, NO_OPERATOR, t1);
}

void join_between_quotes_handler(t_minishell *minishell, t_token_list **list, enum e_token_operators op)
{
	int count;

	count = 1;
	if (*list == NULL || (*list)->next == NULL || (*list)->next->next == NULL)
		return;
	(*list) = (*list)->next;
	while ((*list) && (*list)->next)
	{
		if ((*list)->e_operator == op)
			count++;
		if (count == 2)
			return;
		else if (count == 1 && (*list)->next->e_operator == op)
		{
			(*list) = (*list)->next;
			return;
		} 
		else if (count == 1 ||
				(count == 2 && (*list)->next->e_operator != IS_SPACE && (*list)->next->e_operator != op))
			join_tokens(minishell, list);
		else
			(*list) = (*list)->next;
	}
}

//void join_dollar_and_after_double_quote(t_token_list **list)
//{
//	t_token_list *current = *list;
//
//	while (current != NULL && current->next != NULL)
//	{
//		if (current->e_operator == DOLLAR && current->next->e_operator == DOUBLE_QUOTE)
//		{
//			t_token_list *to_remove = current;
//			current = current->next->next;
//			remove_node(list, to_remove);
//			continue;
//		}
//		current = current->next;
//	}
//}


//void delete_dollar_before_join(t_token_list **list)
//{
//	t_token_list *cpy;
//
//	cpy = *list;
//	while (*list != NULL && (*list)->next != NULL)
//	{
//		if ((*list)->e_operator == DOUBLE_QUOTE && (*list)->next->e_operator == DOLLAR)
//			del_next_token(list);
////		if ((*list)->e_operator == DOLLAR && (*list)->next->e_operator == DOUBLE_QUOTE)
////			remove_node(list, (*list));
//		(*list) = (*list)->next;
//	}
//	*list = cpy;
//}

int check_if_more_tokens(t_token_list **list, enum e_token_operators op)
{
	t_token_list *cpy;

	cpy = (*list)->next;
	while (cpy != NULL)
	{
		if (cpy->e_operator == op)
			return 1;
		cpy = cpy->next;
	}
	return 0;
}


void join_between_quotes(t_minishell *minishell, t_token_list **list)
{
	t_token_list *cpy;

	cpy = *list;
	while (*list != NULL && (*list)->next != NULL)
	{
		if (((*list)->e_operator == DOUBLE_QUOTE && (*list)->next->e_operator == DOUBLE_QUOTE)
		|| ((*list)->e_operator == SINGLE_QUOTE && (*list)->next->e_operator == SINGLE_QUOTE))
		{
			(*list) = (*list)->next;
			(*list) = (*list)->next;
		}
		else if ((*list)->e_operator == DOUBLE_QUOTE && check_if_more_tokens(list, DOUBLE_QUOTE))
		{
			join_between_quotes_handler(minishell, list, DOUBLE_QUOTE);
			if ((*list) == NULL)
				break;
		}
		else if ((*list)->e_operator == SINGLE_QUOTE && check_if_more_tokens(list, SINGLE_QUOTE))
		{;
			join_between_quotes_handler(minishell, list, SINGLE_QUOTE);
			if ((*list) == NULL)
				break;
		}
		else
			(*list) = (*list)->next;
	}
	*list = cpy;

}

void join_dollar_and_single_quote(t_minishell *minishell, t_token_list **list)
{
	t_token_list *cpy;

	cpy = *list;
	while (*list != NULL && (*list)->next != NULL)
	{
		if ((*list)->e_operator == SINGLE_QUOTE && (*list)->next->e_operator == DOLLAR)
		{
			(*list) = (*list)->next;
			if ((*list)->next)
				join_tokens(minishell, list);
			if ((*list) == NULL)
				return ;
		}
		(*list) = (*list)->next;
	}
	*list = cpy;
}

void rename_dollar_token_between_dquote(t_token_list **list)
{
	t_token_list *iterator = *list;
	t_token_list *iterator_prev;


	iterator_prev = NULL;
	while (iterator != NULL && iterator->next != NULL)
	{
		if (iterator_prev && (iterator_prev->e_operator == DOUBLE_QUOTE || iterator_prev->e_operator == SINGLE_QUOTE) && iterator->e_operator == DOLLAR
			&& (iterator->next->e_operator == DOUBLE_QUOTE || iterator->next->e_operator == SINGLE_QUOTE))
		{
			iterator->e_operator = NO_OPERATOR;
			iterator->e_type = COMMAND;
		}
		else
		{
			iterator_prev = iterator;
			iterator = iterator->next;
		}
	}
}

// void join_if_between_quotes(t_token_list **list) {
// 	t_token_list *current = *list;
// 	t_token_list *previous_node = NULL;

// 	while (current != NULL && current->next != NULL && current->next->next != NULL) {
// 		if (current->e_operator == DOUBLE_QUOTE && current->next->e_operator != DOUBLE_QUOTE && current->next->next->e_operator == DOUBLE_QUOTE)
// 		{
// 			if (previous_node)
// 			{
// 				previous_node->next = current->next;
// 				free_token(current);
// 				current->next = current->next->next->next;
// 				free_token(current->next );
// 			} else
// 			{
// 				*list = current->next;
// 				free_token(current);
// 				(*list)->next = current->next->next;
// 				free_token(current->next);
// 				current = *list;
// 			}
// 		} else
// 		{
// 			previous_node = current;
// 			current = current->next;
// 		}
// 	}
// }




void supress_double_quotes(t_token_list **list)
{
	t_token_list *current = *list;
	t_token_list *prev = NULL;

	while (current != NULL && current->next != NULL)
	{
		if (current->e_operator == SINGLE_QUOTE && current->next->e_operator == SINGLE_QUOTE)
		{
			t_token_list *temp = current->next;
			if (prev == NULL)
			{
				*list = temp->next; // Mise à jour du pointeur de début de liste si nécessaire
			}
			else
			{
				prev->next = temp->next; // Relier le nœud précédent au nœud suivant
			}
			free(temp); // Suppression du deuxième nœud
			free(current); // Suppression du premier nœud
			current = prev->next; // Avancer le pointeur actuel vers le prochain nœud après la suppression
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}


//temp = current->next;
//remove_node(begin_list, current);
//current = temp;


void join_between_spaces(t_minishell *minishell, t_token_list **list)
{
	t_token_list *cpy;

	cpy = *list;
	while (*list != NULL && (*list)->next != NULL)
	{
		if ((*list)->e_operator == IS_SPACE)
			*list = (*list)->next;
		while ((*list) != NULL && (*list)->next != NULL && (*list)->next->e_operator != IS_SPACE)
				join_tokens(minishell, list);
		*list = (*list)->next;
	}
	*list = cpy;
}

