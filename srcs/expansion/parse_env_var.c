/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/27 11:29:27 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "utils.h"

void	ft_lsti_insert_after(t_token_list **current, t_token_list *new_token)
{
	if (current == NULL || *current == NULL || new_token == NULL)
		return ;
	new_token->next = (*current)->next;
	(*current)->next = new_token;
}

int	insert_env_token(char *string, t_token_list **current)
{
	t_token_list	*new_token;

	new_token = ft_calloc(1, sizeof(t_token_list));
	if (new_token == NULL)
		return (MALLOC_FAILED);
	if (define_token(new_token, string) == MALLOC_FAILED)
	{
		free(new_token);
		return (MALLOC_FAILED);
	}
	new_token->parsed = 1;
	ft_lsti_insert_after(current, new_token);
	return (0);
}

void	free_for_add_tokens(t_minishell *m, char *string, char ***split)
{
	ft_free_tab(split);
	free(string);
	exit_msg(m, "Malloc failed at add_tokens", ENOMEM);
}

void	split_and_expand(t_minishell *m, t_token_list **list, char *string)
{
	char			**split;
	int				i;
	t_token_list	*current;

	i = 0;
	split = ft_split(string, ' ');
	if (split == NULL)
	{
		free(string);
		exit_msg(m, "Malloc failed at add_tokens", ENOMEM);
	}
	current = *list;
	while (split[i])
	{
		if (insert_env_token(split[i], &current) == MALLOC_FAILED)
			free_for_add_tokens(m, string, &split);
		current = current->next;
		i++;
	}
	ft_free_tab(&split);
}
