/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:43:37 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/19 09:43:37 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include "parser.h"

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

void create_cmd_table(t_minishell *minishell, t_node **list_tokens)
{
	int nbr_cmd_until_pipe;

	nbr_cmd_until_pipe = count_tokens_until_pipe_or_redirect(*list_tokens);
	minishell->cmd_table = malloc((nbr_cmd_until_pipe + 1) * sizeof(char **));
	if (minishell->cmd_table == NULL)
		return;
	fill_array(list_tokens, minishell->cmd_table, nbr_cmd_until_pipe);
}

char **create_in_redirect_table(t_node **list_tokens)
{
	int		nbr_cmd_until_pipe;
	char	**redirection_array;

	nbr_cmd_until_pipe = count_tokens_from_in_redirect(*list_tokens);
	if (nbr_cmd_until_pipe != 0)
	{
		redirection_array = malloc((nbr_cmd_until_pipe + 1) * sizeof(char **));
		if (redirection_array == NULL)
			return (NULL);
		fill_array(list_tokens, redirection_array, nbr_cmd_until_pipe);
		return (redirection_array);
	}
	return (NULL);
}

char **create_out_redirect_table(t_node **list_tokens)
{
	int		nbr_cmd_until_pipe;
	char	**redirection_array;

	nbr_cmd_until_pipe = count_tokens_from_out_redirect(*list_tokens);
	if (nbr_cmd_until_pipe != 0)
	{
		redirection_array = malloc((nbr_cmd_until_pipe + 1) * sizeof(char **));
		if (redirection_array == NULL)
			return (NULL);
		fill_array(list_tokens, redirection_array, nbr_cmd_until_pipe);
		return (redirection_array);
	}
	return (NULL);
}

void create_redirect_table(t_minishell *minishell, t_node **list_tokens)
{
	minishell->in_redirect_table = create_in_redirect_table(list_tokens);
	minishell->out_redirect_table = create_out_redirect_table(list_tokens);
}
