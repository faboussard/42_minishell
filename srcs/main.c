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
#include "parser.h"

t_hashmap_struct *create_dict_envp(char **envp);

void create_token_chain_list(t_minishell *minishell, char *string)
{
	minishell->list_tokens = get_list_tokens(string);
}

void create_envp_hashmap(t_minishell *minishell, char **envp)
{
	minishell->hashmap_environment = create_dict_envp(envp);
}

void create_tables(t_minishell *minishell)
{
	create_cmd_table(minishell, minishell->list_tokens);
	create_envp_table(minishell, &minishell->hashmap_environment);
}

void	ft_init_minishell(t_minishell *minishell)
{
	ft_bzero(minishell, (sizeof * minishell));
	minishell->status = 0;
	minishell->fd_in = -1;
	minishell->fd_out = -1;
}


int main()
{
	/******* dans int main(int ac, char **av, char **env) *****/
	char *string = "lsffffff ls > ll | ll"; //entree dans readlin, avant split par "bash"
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
	print_envp_dict(minishell.hashmap_environment->dict_chain); //DELETE
	create_tables(&minishell);
	ft_printf("************ print cmd_table ************\n");
	print_array(minishell.cmd_table);  //DELETE
	ft_printf("********************** print HM table **********************\n");
	print_array(minishell.envp_table);  //DELETE
	free_minishell(&minishell);
	return (0);
}


