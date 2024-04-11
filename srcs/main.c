/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/11 10:17:52 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "signals.h"
#include "utils.h"
#include <readline/history.h>

#define PROMPT "\001\e[27m\002>>> \001\e[0m\e[45m\002 Minishell>$ \001\e[0m\002"

void minishell_interactive(t_minishell *minishell)
{
	while (1)
	{
		set_signals_interactive();
		minishell->user_input = readline(PROMPT);
		if (minishell->user_input == NULL)
			break;
		if (minishell->user_input[0] == 0)
			continue;
		set_signals_noninteractive();
		add_history(minishell->user_input);
		if (parse_input(minishell) == 0)
		{
			if (minishell->process_list == NULL)
				return;
			ft_init_process_list_and_minishell(minishell, minishell->process_list);
			exec_builtin(minishell, minishell->list_tokens);
			ft_init_process_list_and_minishell(minishell, minishell->process_list);
			execute_cmds(minishell, minishell->total_commands);
		}
		free(minishell->user_input);
		ft_free_process_list(&(minishell->process_list));
		ft_lstclear_token(&minishell->list_tokens);
	}
}

char *expand_input(char *input, t_minishell *minishell);

void minishell_non_interactive(t_minishell *minishell, char *data_input)
{
	set_signals_noninteractive();
//	char *input = "$USER $USER";
//	input = expand_input(input, minishell);
	minishell->user_input = NULL;
	minishell->user_input = ft_strdup(data_input);
	if (minishell->user_input == NULL)
		exit_msg(minishell, "Fatal : malloc failed", -1);
	add_history(minishell->user_input);
	if (parse_input(minishell) == 0)
	{
		if (minishell->process_list == NULL)
			return;
		exec_builtin(minishell, minishell->list_tokens);
		ft_init_process_list_and_minishell(minishell, minishell->process_list);
//		execute_cmds(minishell, minishell->total_commands);
	}
}

int main(int ac, char **av, char **envp)
{
	t_minishell minishell;

	ft_init_minishell(&minishell, ac, av);
	if (envp)
		minishell.list_envp = create_envp_list(envp, &minishell);
	if (minishell.list_envp == NULL)
		exit_msg(&minishell, "Fatal : malloc failed", -1);
	if (is_interactive(&minishell, ac) == true)
		minishell_interactive(&minishell);
	else
		minishell_non_interactive(&minishell, av[2]);
//	  printf("************ print list_envp ************\n\n"); // DELETE
//	  print_list_envp(&minishell);
	printf("************ print list_tokens ************\n"); // DELETE
	print_token_list(minishell.list_tokens); //DELETE
	printf("************ process list (cmd table , in out files,limiters : ********* \n"); // DELETE
	print_process_list(minishell.process_list); // DELETE
//	   printf("********************** print env_table **********************\n\n");
//		print_array(minishell.envp_table);  //DELETE
	free_minishell(&minishell);
	return (0);
}
