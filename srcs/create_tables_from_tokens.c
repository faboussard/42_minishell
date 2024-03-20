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

void create_cmd_table(t_minishell *minishell, t_node **list_tokens)
{
	int nbr_cmd_until_pipe;

	nbr_cmd_until_pipe = count_tokens_until_pipe_or_redirect(*list_tokens);
	minishell->cmd_table = malloc((nbr_cmd_until_pipe + 1) * sizeof(char **));
	if (minishell->cmd_table == NULL)
		return;
	fill_array(list_tokens, minishell->cmd_table, nbr_cmd_until_pipe);
}

void create_envp_table(t_minishell *minishell, t_dict envp_dict)
{
	t_dict_content *envp_dict_node;
	t_node *current;
	int i;
	int j;

	j = 0;
	i = HASHMAP_ARR_SIZE;
	minishell->envp_table = malloc(1000* sizeof(char **));
	while (i-- > 0)
	{
		current = envp_dict[i];
		while (current)
		{
			envp_dict_node = (t_dict_content *)current->content;
			minishell->envp_table[j] = malloc(1000 * sizeof(char *));
			if (minishell->envp_table == NULL)
				return;
			minishell->envp_table[j] = ft_strjoin((char *)envp_dict_node->target, "=");
			minishell->envp_table[j] = ft_strjoin(minishell->envp_table[j], envp_dict_node->content);
			if (minishell->envp_table[j] == NULL)
				return;
			current = current->next;
			j++;
		}
	}
}
