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
#include "parser.h"
#include "signals.h"

void	set_environment(t_minishell *m, char **envp)
{
	m->list_envp = create_envp_list(envp, m);
	if (m->list_envp == NULL)
		create_3_env_variables(m);
	if (m->list_envp == NULL)
		exit_msg(m, "Malloc failed at main", ENOMEM);
}

void	minishell_interactive(t_minishell *m)
{
	while (1)
	{
		if (set_signals_interactive() == -1)
			m->status = set_or_get_last_status(-1, -1);
		m->user_input = readline(PROMPT);
		if (m->user_input == NULL)
			break ;
		if (m->user_input[0] == 0)
			continue ;
		if (set_signals_noninteractive() == -1)
			m->status = set_or_get_last_status(-1, -1);
		add_history(m->user_input);
		m->status = set_or_get_last_status(-1, -1);
		if (parse_input(m) == 0)
		{
			if (m->pl == NULL)
				continue ;
			ft_init_pl(m, m->pl);
			execute_cmds(m, m->total_commands);
		}
		init_before_next_prompt(m);
	}
}

void	minishell_non_interactive(t_minishell *m, char *data_input)
{
	m->user_input = ft_strdup(data_input);
	if (m->user_input == NULL)
		exit_msg(m,
				 "Fatal : malloc failed at minishell_non_interactive", 2);
	if (set_signals_noninteractive() == -1)
		m->status = set_or_get_last_status(-1, -1);
	if (parse_input(m) == 0)
	{
		if (m->pl == NULL)
			return ;
		execute_cmds(m, m->total_commands);
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

//int	main(int ac, char **av, char **envp)
//{
//	t_minishell	minishell;
//	char	*readline_input;
//	char	**arg_input;
//	int		i;
//
//	if (ac == 3 && ft_strcmp(av[1], "-c") == 0 && av[2])
//	{
//		arg_input = ft_split(av[2], ';');
//		if (!arg_input)
//			return (1);
//		i = 0;
//		while (arg_input[i])
//		{
//			ft_bzero(&minishell, (sizeof(t_minishell)));
//			minishell.total_commands = 1;
//			set_minishell_paths(&minishell);
//			set_environment(&minishell, envp);
////			if (is_interactive(&minishell, ac, av) == true)
////				minishell_interactive(&minishell);
////			else
//				minishell_non_interactive(&minishell, arg_input[i]);
//			// Parse arg_input[i]
//			// Execute arg_input[i]
//			i++;
//		}
//	}
//	else
//	{
//		while (1)
//		{
//			readline_input = readline(PROMPT);
//			ft_bzero(&minishell, (sizeof(t_minishell)));
//			minishell.total_commands = 1;
//			set_minishell_paths(&minishell);
//			set_environment(&minishell, envp);
////			if (is_interactive(&minishell, ac, av) == true)
////				minishell_interactive(&minishell);
////			else
//				minishell_non_interactive(&minishell, readline_input);
//			//Parse readline input
//			//Execute readline input
//		}
//	}
//	// Free data and exit minishell when done
//	free_minishell(&minishell);
//	return (minishell.status);
//}

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