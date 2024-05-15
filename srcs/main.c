/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/09 21:37:03 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "parser.h"
#include "signals.h"
#include "utils.h"
#include <readline/history.h>

void	set_environment(t_minishell *m, char **envp)
{
	m->list_envp = create_envp_list(envp, m);
	if (m->list_envp == NULL)
		create_3_env_variables(m);
	if (m->list_envp == NULL)
		exit_msg(m, "Malloc failed at main", ENOMEM);
}

bool	is_one_arg_builtin(t_minishell *m)
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
		init_before_next_prompt(m);
	}
}

//if (m->list_envp == NULL) // check on unset tout avec pipe et sans pipe
//	return ;
// --> La list_envp doit au moins contenir _= /usr/bin/env
void	minishell_non_interactive(t_minishell *minishell, char *data_input)
{
	minishell->user_input = ft_strdup(data_input);
	if (minishell->user_input == NULL)
		exit_msg(minishell,
			"Fatal : malloc failed at minishell_non_interactive", ENOMEM);
	set_signals_noninteractive();
	if (parse_input(minishell) == 0)
	{
		if (minishell->pl == NULL)
			return ;
		execute_cmds(minishell, minishell->total_commands);
	}
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

// minishell->user_input = ft_strtrim(minishell->user_input, "\"");
/*
	Ma gestion des protections malloc est alambiquée mais doit fonctionner :
	Si temp N'est PAS NULL, alors on alloue minishell->user_input.
	Si minishell->user_input est NULL, l'un des deux mallocs a échoué, donc exit
	(d'ailleurs, plutot juste un message d'erreur + un return
	sans fermer tout le minishell serait bien ici je pense)
	Et toujours des free_safely_str avant de vérifier le malloc pour ne
 	pas exit/return avant d'avoir free un malloc

 void	format_input(t_minishell *m, char **av)
{
	int			i;
	char		*temp;

	m->user_input = ft_calloc(1, 1);
	if (m->user_input == NULL)
		exit_msg(m, "Malloc failed at format_input", -1);
	i = 0;
	while (av[i])
	{
		temp = ft_strjoin(m->user_input, av[i]);
		free_safely_str(&(m->user_input));
		if (temp != NULL)
			m->user_input = ft_strdup(temp);
		free_safely_str(&(temp));
		if (m->user_input == NULL)
			exit_msg(m, "Malloc failed at format_input", -1);
		i++;
	}
	temp = ft_strdup(m->user_input);
	free_safely_str(&(m->user_input));
	if (temp != NULL)
		m->user_input = ft_strtrim(temp, "\"");
	free_safely_str(&temp);
	if (m->user_input == NULL)
		exit_msg(m, "Malloc failed at format_input", -1);
}*/

int	main(int ac, char **av, char **envp)
{
	t_minishell	minishell;

	ft_bzero(&minishell, (sizeof(t_minishell)));
	minishell.total_commands = 1;
	set_minishell_paths(&minishell);
	set_environment(&minishell, envp);
	if (is_interactive(&minishell, ac, av) == true)
		minishell_interactive(&minishell);
	else
		minishell_non_interactive(&minishell, av[2]);
	//	ft_print_minishell(&minishell);
	free_minishell(&minishell);
	return (minishell.status);
}
