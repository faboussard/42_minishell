/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                			                    :+:      :+:    :+:   */
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

void create_token_chain_list(t_minishell *minishell, char *string)
{
	minishell->list_tokens = get_list_tokens(string);
}

void create_envp_hashmap(t_minishell *minishell, char **envp)
{
	minishell->hm_env_variables = get_hm_env_variables(envp);
}

void create_tables(t_minishell *minishell)
{
	create_cmd_table(minishell, minishell->list_tokens);
	create_redirect_table(minishell, minishell->list_tokens);
}

int main()
{
	/******* dans int main(int ac, char **av, char **env) *****/
	char *string = "ls l < cat cat |"; //entree dans readlin, avant split par "bash"
	char			*envp[] = {
			"PATH=/bin:/usr/bin",
			"HOME=/home/user",
			"USER=user",
			NULL
	};
	/*************************************************************/
	t_minishell 	minishell;

	ft_init_minishell(&minishell);
	create_token_chain_list(&minishell, string);
	print_token(minishell.list_tokens); //DELETE
	create_envp_hashmap(&minishell, envp);
	print_hashmap(minishell.hm_env_variables); //DELETE
	create_tables(&minishell);
	print_array(minishell.cmd_table);
	print_array(minishell.in_redirect_table);
	free_minishell(&minishell);
	return (0);
}


