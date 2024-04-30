/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/22 09:45:40 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"
#include "minishell.h"
#include "parser.h"
#include "signals.h"
#include "utils.h"
#include <readline/history.h>

bool is_one_arg_builtin(t_minishell *m)
{
	if (m->list_tokens->e_builtin == EXIT)
		return (1);
	if (m->list_tokens->e_builtin == ENV)
		return (1);
	if (m->list_tokens->e_builtin == UNSET)
		return (1);
	if (m->list_tokens->e_builtin == CD)
		return (1);
	if (m->list_tokens->e_builtin == EXPORT)
		return (1);
	return (0);
}
void	minishell_interactive(t_minishell *m)
{
	while (1)
	{
		set_signals_interactive();
		m->user_input = readline(PROMPT);
		if (m->user_input == NULL)
			break ;
		if (m->user_input[0] == 0)
			continue ;
		set_signals_noninteractive();
		add_history(m->user_input);
		m->status = set_or_get_last_status(-1, -1);
		if (parse_input(m) == 0)
		{
			if (m->pl == NULL)
				continue ;
			ft_init_pl(m, m->pl);
			if (m->total_commands == 1 && is_one_arg_builtin(m))
				is_a_builtin(m, m->pl->cmd_table[0], m->pl->cmd_table);
			else
				execute_cmds(m, m->total_commands);
		}
		m->total_commands = 1;
		// CAPITAL ! L'ORIGINE DE NOS SEGFAULTS : LE TOTAL_COMMANDS QUI NE SE REMET
		// PAS A 1 ENTRE DEUX PROMPTS !
		free(m->user_input);
		ft_free_process_list(&(m->pl));
		ft_lstclear_token(&m->list_tokens);
		if (m->envp_table)
			ft_free_all_tab(m->envp_table);
	}
}

void	minishell_non_interactive(t_minishell *minishell, char *data_input)
{
	minishell->user_input = ft_strdup(data_input);
	if (minishell->user_input == NULL)
		exit_msg(minishell, "Fatal : malloc failed at minishell_non_interactive", 2);
	set_signals_noninteractive();
	if (parse_input(minishell) == 0)
	{
		if (minishell->pl == NULL)
			return ;
        execute_cmds(minishell, minishell->total_commands);
	}
}

void	ft_print_minishell(t_minishell *minishell)
{
	printf("************ print list_envp ************\n\n");
	print_list_envp(minishell);
	printf("************ print list_tokens ************\n");
	print_token_list(minishell->list_tokens);
	// DELETE
	printf("************ process list (cmd table ,in out files,limiters : ********* \n");
	// DELETE
	print_process_list(minishell->pl);
	printf("********************** print env_table**********************\n\n");
	print_array(minishell->envp_table);
}

bool	is_interactive(t_minishell *minishell, int argc, char **argv)
{
	if (argc == 1 || ft_strncmp(argv[1], "-c", 2) != 0)
	{
		minishell->interactive = true;
		return (true);
	}
	else if (argc > 2 && ft_strncmp(argv[1], "-c", 2) == 0)
	{
		minishell->interactive = false;
		return (false);
	}
	else
	{
		exit_msg(minishell,
					"Wrong arguments.\nUsage:\nNon_interactive mode\
						-./ minishell - c \"input line\" \nInteractive mode \
						-./ minishell ",
					-1);
	}
	return (2);
}
// minishell->user_input[0] = '\0'; // inutile : calloc remplit déja avec des \0
/*
temp = ft_strdup(av[i]);
minishell->user_input = ft_strjoin(minishell->user_input, temp);
--> leaks assurés ici. Version modifiée ci-dessous dans la fonction non commentée
*/
// minishell->user_input = ft_strtrim(minishell->user_input, "\"");
/*
	Ma gestion des protections malloc est alambiquée mais doit fonctionner :
	Si temp N'est PAS NULL, alors on alloue minishell->user_input.
	Si minishell->user_input est NULL, l'un des deux mallocs a échoué, donc exit
	(d'ailleurs, plutot juste un message d'erreur + un return
	sans fermer tout le minishell serait bien ici je pense)
	Et toujours des free_safely_str avant de vérifier le malloc pour ne pas exit/return avant d'avoir free un malloc
*/
void	format_input(t_minishell *minishell, char **av)
{
	int		i;
	char	*temp;

	minishell->user_input = ft_calloc(1, 1);
	if (minishell->user_input == NULL)
		exit_msg(minishell, "Malloc failed at format_input", -1);
	i = 0;
	while (av[i])
	{
		temp = ft_strjoin(minishell->user_input, av[i]);
		free_safely_str(minishell->user_input);
		if (temp != NULL)
			minishell->user_input = ft_strdup(temp);
		free_safely_str(temp);
		if (minishell->user_input == NULL)
			exit_msg(minishell, "Malloc failed at format_input", -1);
		i++;
	}
	temp = ft_strdup(minishell->user_input);
	free_safely_str(minishell->user_input);
	if (temp != NULL)
		minishell->user_input = ft_strtrim(temp, "\"");
	free_safely_str(temp);
	if (minishell->user_input == NULL)
		exit_msg(minishell, "Malloc failed at format_input", -1);
}

//void create_3_env_variables(t_minishell *minishell)
//{
//	export
//	PWD=/home/faboussa
//	SHLVL=1
//	_=/usr/bin/env
//

//declare -x OLDPWD
//declare -x PWD="/home/faboussa"
//declare -x SHLVL="1"

//}

int	main(int ac, char **av, char **envp)
{
	t_minishell	minishell;

	ft_bzero(&minishell, (sizeof(t_minishell)));
	minishell.total_commands = 1;
	if (envp)
		minishell.list_envp = create_envp_list(envp, &minishell);
	if (minishell.list_envp == NULL)
		exit_msg_minishell(&minishell, "Environement variables could not be created", -1);
	set_minishell_paths(&minishell);
	if (is_interactive(&minishell, ac, av) == true)
		minishell_interactive(&minishell);
	else
		minishell_non_interactive(&minishell, av[2]);
//	ft_print_minishell(&minishell);
	free_minishell(&minishell);
	return (minishell.status);
}
