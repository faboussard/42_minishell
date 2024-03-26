/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                			                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/22 12:10:15 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"
#include "minishell.h"
#include "utils.h"
#include "parser.h"

void	ft_init_minishell(t_minishell *minishell)
{
	ft_bzero(&minishell, (sizeof(t_minishell)));
	minishell->fd_in = -1;
	minishell->fd_out = -1;
}

void create_token_chain_list(t_minishell *minishell, char *string)
{
	minishell->list_tokens = get_list_tokens(string);
}

void create_envp_hashmap(t_minishell *minishell, char **envp)
{
	minishell->hashmap_environment = create_dict_envp(envp);
}

/******for exec*******/
void create_tables(t_minishell *minishell)
{
	create_cmd_table(minishell, minishell->list_tokens);
	create_envp_table(minishell, &minishell->hashmap_environment);
}