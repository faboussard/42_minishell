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

void fill_array(t_node *list_tokens, char **array, size_t nbr_cmds)
{
	t_token *token;
	size_t i;

	i = 0;
	while (i < nbr_cmds && list_tokens != NULL)
	{
		token = (t_token *)list_tokens->content;
		array[i] = ft_strdup(token->name);
		if (array[i] == NULL)
			return;
		i++;
		list_tokens = list_tokens->next;
	}
	array[i] = NULL;
}


void create_cmd_table(t_minishell *minishell, t_node *list_tokens)
{
	size_t nbr_cmds_until_redirect_or_pipe;
	size_t nbr_letters_until_redirect_or_pipe;

	nbr_cmds_until_redirect_or_pipe = count_cmds_until_pipe_or_redirect(list_tokens);
	nbr_letters_until_redirect_or_pipe = count_letters_until_pipe_or_redirect(list_tokens);
	minishell->cmd_table = ft_calloc(nbr_letters_until_redirect_or_pipe, sizeof(char **));
	if (minishell->cmd_table == NULL)
		return;
	fill_array(list_tokens, minishell->cmd_table, nbr_cmds_until_redirect_or_pipe);
}

void create_envp_table(t_minishell *minishell)
{
	t_envp_content *envp_node = minishell->list_envp;
	size_t total_target_and_value_size = calculate_total_size(minishell);
	size_t j = 0;
	char *temp;

	minishell->envp_table = ft_calloc(total_target_and_value_size + 1, sizeof(char *));
	if (minishell->envp_table == NULL)
		return;

	while (envp_node != NULL)
	{
		temp = ft_strjoin(envp_node->target, "=");
		if (temp == NULL)
			return;
		minishell->envp_table[j] = ft_strjoin(temp, envp_node->value);
		free(temp);
		if (minishell->envp_table[j] == NULL)
			return;

		envp_node = envp_node->next;
		j++;
	}
	minishell->envp_table[j] = NULL;
}


void create_tables(t_minishell *minishell)
{
	if (minishell->list_tokens != NULL)
		create_cmd_table(minishell, minishell->list_tokens);
	if (minishell->list_envp != NULL)
		create_envp_table(minishell);
}

