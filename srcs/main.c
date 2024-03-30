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
#include "signals.h"
# include <readline/history.h>
# include "execute.h"
#include "parser.h"

# define PROMPT "\001\e[27m\002>>> \001\e[0m\e[45m\002 Minishell>$ \001\e[0m\002"

void minishell_interactive(t_minishell *minishell)
{
    while (1)
    {
        set_signals_interactive();
        minishell->user_input = readline(PROMPT);
        if (minishell->user_input == NULL)
            break;
        set_signals_noninteractive();
        add_history(minishell->user_input);
        minishell->history_count += 1;
        minishell->list_tokens = parse_input(minishell);
        if (minishell->list_tokens == NULL)
            exit_msg(minishell, "Fatal : tokenization failed", -1);
        create_tables(minishell);
        free(minishell->user_input);
    }
}

void minishell_non_interactive(t_minishell *minishell, char *data_input)
{
	set_signals_noninteractive();
	minishell->user_input = ft_strdup(data_input);
	if (minishell->user_input == NULL)
		exit_msg(minishell, "Fatal : malloc failed", -1);
	add_history(minishell->user_input);
	minishell->history_count += 1;
	minishell->list_tokens = parse_input(minishell);
	if (minishell->list_tokens == NULL)
		return ;
	create_tables(minishell);
}

int main(int ac, char **av, char **envp)
{
	t_minishell 	minishell;

	ft_init_minishell(&minishell, ac, av);
	if (envp)
		minishell.list_envp = create_envp_list(envp, &minishell);
	if (minishell.list_envp == NULL)
		exit_msg(&minishell, "Fatal : malloc failed", -1);
	if (is_interactive(&minishell, ac) == true)
		minishell_interactive(&minishell);
	else
		minishell_non_interactive(&minishell, av[2]);
//    printf("************ print list_envp ************\n\n"); // DELETE
//    print_list_envp(&minishell);
//    printf("************ print list_tokens **********\n\n"); // DELETE
//    print_token_list(minishell.list_tokens); //DELETE
//    printf("************ print cmd_table ************\n\n"); // DELETE
//	print_array(minishell.cmd_table);  //DELETE
//    printf("************ print env_table *************\n\n"); // DELETE
//	print_array(minishell.envp_table);  //DELETE
	free_minishell(&minishell);
	return (0);
}


