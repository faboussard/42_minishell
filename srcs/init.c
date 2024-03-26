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

t_hashmap_struct *create_dict_envp(char **envp);

void	ft_init_minishell(t_minishell *minishell, char **envp)
{
	if (!init_envp(minishell, envp))
		return (ft_putendl_fd("Fatal : Could not initialize envp", 2));
	if (!init_words(minishell))
		return (ft_putendl_fd("Fatal : could not initialize working directory", 2));
	ft_bzero(minishell, (sizeof * minishell));
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