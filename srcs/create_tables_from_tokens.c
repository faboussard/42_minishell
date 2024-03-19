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

int count_tokens_until_pipe_or_redirect(t_node *head)
{
	int		num_commands;
	t_node	*current;
	t_token	*token;

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

int count_tokens_until_redirect(t_node *head)
{
	int		num_commands;
	t_node	*current;
	t_token	*token;

	num_commands = 0;
	current = head;
	while (current)
	{
		token = (t_token *) (current)->content;
		if (!is_redirect_token(token))
			num_commands++;
		else
			break ;
		current = current->next;
	}
	return (num_commands);
}

int count_tokens_from_redirect(t_node *head)
{
	int		i;
	int		num_commands;
	t_node	*current;
	t_token	*token;

	current = head;
	i = count_tokens_until_redirect(head);
	num_commands = i;
	while (current)
	{
		token = (t_token *) (current)->content;
		if (token->e_operator != PIPE)
			num_commands++;
		current = current->next;
	}
	return (num_commands - i);
}

void fill_array(t_node **list_tokens, char **array, int cmd_until_pipe)
{
	t_token	*token;
	int		i;

	i = 0;
	while (i < cmd_until_pipe)
	{
		token = (t_token *) (*list_tokens)->content;
		array[i] = ft_strdup(token->name);
		if (array[i] == NULL)
			return ;
		i++;
		*list_tokens = (*list_tokens)->next;
	}
	array[i] = NULL;
}

void create_cmd_table(t_minishell *minishell, t_node *list_tokens)
{
	int nbr_cmd_until_pipe;

	nbr_cmd_until_pipe = count_tokens_until_pipe_or_redirect(list_tokens);
	minishell->cmd_table = malloc((nbr_cmd_until_pipe + 1) * sizeof(char **));
	if (minishell->cmd_table == NULL)
		return;
	fill_array(&list_tokens, minishell->cmd_table, nbr_cmd_until_pipe);
}

char **create_in_redirect_table(t_node *list_tokens)
{
	int		nbr_cmd_until_pipe;
	char	**redirection_array;

	nbr_cmd_until_pipe = count_tokens_from_redirect(list_tokens);
	redirection_array = malloc((nbr_cmd_until_pipe + 1) * sizeof(char **));
	if (redirection_array == NULL)
		return (NULL);
	fill_array(&list_tokens, redirection_array, nbr_cmd_until_pipe);
	return (redirection_array);
}

void create_redirect_table(t_minishell *minishell, t_node *list_tokens)
{
	minishell->in_redirect_table = create_in_redirect_table(list_tokens);
//	minishell->out_redirect_table = create_out_redirect_table(list_tokens);
}
