/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/30 22:28:06 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "utils.h"
#include "signals.h"
#include "parser.h"
# include <readline/history.h>

# define PROMPT "\001\e[27m\002>>> \001\e[0m\e[45m\002 Minishell>$ \001\e[0m\002"

void minishell_interactive(t_minishell *minishell)
{
	while (1)
	{
		set_signals_interactive();
		minishell->user_input = readline(PROMPT);
		if (minishell->user_input == NULL)
			break;
		printf("the command is %s\n", minishell->user_input);

		if (minishell->user_input[0] == 0)
			continue;
		set_signals_noninteractive();
//        add_history(minishell->user_input);
		minishell->history_count += 1;
		parse_input(minishell);
		create_process_list(minishell);
		printf("the process list first cmd is %s\n", minishell->process_list->cmd_table[0]);
		printf("the process list first cmd is %s\n", minishell->process_list->cmd_table[1]);
		if (minishell->process_list == NULL)
			return ;
		execute_cmds(minishell, minishell->total_commands);
		free(minishell->user_input);
		ft_free_process_list(&(minishell->process_list));
		ft_lstclear_token(&minishell->list_tokens);
	}
}

void minishell_non_interactive(t_minishell *minishell, char *data_input)
{
	set_signals_noninteractive();
	minishell->user_input = ft_strdup(data_input);
	if (minishell->user_input == NULL)
		exit_msg(minishell, "Fatal : malloc failed", -1);
//	add_history(minishell->user_input);
	minishell->history_count += 1;
	parse_input(minishell);
	create_process_list(minishell);
	printf("total command is %zu\n", minishell->total_commands);
	execute_cmds(minishell, minishell->total_commands);
}

int main(int ac, char **av, char **envp)
{
	t_minishell 	minishell;

	ft_init_minishell(&minishell, ac, av);
	if (envp)
		minishell.list_envp = create_envp_list(envp, &minishell);
	if (minishell.list_envp == NULL)
		exit_msg(&minishell, "Fatal : malloc failed", -1);
	else
		create_envp_table(&minishell);
	if (is_interactive(&minishell, ac) == true)
		minishell_interactive(&minishell);
	else
		minishell_non_interactive(&minishell, av[2]);
    printf("************ print list_envp ************\n\n"); // DELETE
    print_list_envp(&minishell);
	printf("************ print list_tokens ************\n"); // DELETE
	print_token_list(minishell.list_tokens); //DELETE
	printf("************ process list (cmd table , in out files, limiters : ********* \n"); // DELETE
	print_process_list(minishell.process_list);  //DELETE
    printf("********************** print env_table **********************\n\n"); // DELETE
	print_array(minishell.envp_table);  //DELETE
	free_minishell(&minishell);
	return (0);
}
