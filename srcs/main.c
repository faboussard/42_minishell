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
	print_token(minishell->list_tokens);
}

void create_envp_hashmap(t_minishell *minishell, char **envp)
{
	minishell->hm_env_variables = get_hm_env_variables(envp);
	print_hashmap(minishell->hm_env_variables);
}

int main()
{
	/******* dans int main(int ac, char **av, char **env) *****/
	char *string = "echo cat | .txt"; //entree dans readlin, avant split par "bash"
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
	create_envp_hashmap(&minishell, envp);

	tokens_to_array_of_cmds(&minishell, minishell.list_tokens);
	tokens_to_redirects(&minishell, minishell.list_tokens);
	print_array(minishell.token_array);
	free_minishell(&minishell);
	return (0);
}


