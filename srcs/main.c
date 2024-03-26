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

#include "lexer.h"
#include "minishell.h"
#include "utils.h"
#include "parser.h"
#include "minishell.h"

void minishell_interactive(t_minishell *minishell, char **envp)
{
	while (1)
	{
		minishell->list_tokens = readline(PROMPT);
		minishell->hashmap_environment = create_envp_hm(envp);
		print_envp_dict(minishell.hashmap_environment->dict_chain); //DELETE
		create_tables(minishell);
	}
}

void minishell_non_interactive(t_minishell *minishell, char *data_input, char **envp)
{
	minishell->list_tokens = get_list_tokens(data_input);
	minishell->hashmap_environment = create_envp_hm(envp);
	print_envp_dict(minishell->hashmap_environment->dict_chain); //DELETE
	create_tables(minishell);
}

int main(int ac, char **av, char **envp)
{
	t_minishell 	minishell;

	ft_init_minishell(&minishell, ac, av);
	if (is_interactive(&minishell, ac) == true)
		minishell_interactive(&minishell, envp);
	else
		minishell_non_interactive(&minishell, av[2], envp);

	print_token(minishell.list_tokens); //DELETE
	/**** for exec *///////
	ft_printf("************ print cmd_table ************\n\n");
	print_array(minishell.cmd_table);  //DELETE
	ft_printf("********************** print HM table **********************\n\n");
	print_array(minishell.envp_table);  //DELETE
	/**** for exec *///////

	free_minishell(&minishell);
	return (0);
}


