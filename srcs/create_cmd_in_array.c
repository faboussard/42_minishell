/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:43:37 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/19 09:43:37 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

int count_tokens_until_pipe(t_node *head)
{
	int num_commands;
	t_node *current;
	t_token *token;

	num_commands = 0;
	current = head;
	while (current)
	{
		token = (t_token *) (current)->content;
		if (token->e_operator != PIPE && !is_redirect_token(token))
			num_commands++;
		else
			break ;
		current = current->next;
	}
	return (num_commands);
}

void fill_array(t_node *list_tokens, char **array, int cmd_until_pipe)
{
	t_node	*current;
	t_token	*token;
	int		i;

	current = list_tokens;
	i = 0;
	while (i < cmd_until_pipe)
	{
		token = (t_token *) (current)->content;
		array[i] = ft_strdup(token->name);
		if (array[i] == NULL)
			return ;
		i++;
		current = current->next;
	}
	array[i] = NULL;
}

void tokens_to_array_of_cmds(t_minishell *minishell, t_node *list_tokens)
{
	int nbr_cmd_until_pipe;

	nbr_cmd_until_pipe = count_tokens_until_pipe(list_tokens);
	minishell->token_array = malloc((nbr_cmd_until_pipe + 1) * sizeof(char **));
	if (minishell->token_array == NULL)
		return;
	fill_array(list_tokens, minishell->token_array, nbr_cmd_until_pipe);
}

void tokens_to_redirects(t_minishell *minishell, t_node *list_tokens)
{
	int nbr_cmd_until_pipe;

	nbr_cmd_until_pipe = count_tokens_until_pipe(list_tokens);
	minishell->token_array = malloc((nbr_cmd_until_pipe + 1) * sizeof(char **));
	if (minishell->token_array == NULL)
		return;
	fill_array(list_tokens, minishell->token_array, nbr_cmd_until_pipe);
}
