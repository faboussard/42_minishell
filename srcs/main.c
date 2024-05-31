/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/30 20:19:00 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "signals.h"

static void	set_environment(t_minishell *m, char **envp)
{
	m->list_envp = create_envp_list(envp, m);
	if (m->list_envp == NULL)
		create_3_env_variables(m);
	if (m->list_envp == NULL)
		exit_msg(m, "Malloc failed at main", ENOMEM);
}

static void	minishell_interactive(t_minishell *m)
{
	while (1)
	{
		if (set_signals_interactive() == -1)
			m->status = set_or_get_last_status(-1, -1);
		free_safely_str(&m->user_input);
		m->user_input = readline(PROMPT);
		if (m->user_input == NULL)
		{
			print_error("exit");
			break ;
		}
		if (m->user_input[0] == 0)
			continue ;
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

static void	minishell_non_interactive(t_minishell *m, char *data_input)
{
	if (!data_input)
		exit_msg(m, "bash: -c: option requires an argument", 2);
	m->user_input = ft_strdup(data_input);
	if (m->user_input == NULL)
		exit_msg(m, "Fatal : malloc failed at minishell_non_interactive",
			ENOMEM);
	if (set_signals_noninteractive() == -1)
		m->status = set_or_get_last_status(-1, -1);
	if (parse_input(m) == 0)
	{
		if (m->pl == NULL)
			return ;
		ft_init_pl(m, m->pl);
		execute_cmds(m, m->total_commands);
	}
}

static bool	is_interactive(t_minishell *minishell, int argc, char **argv)
{
	if (argc == 1 || ft_strncmp(argv[1], "-c", 2) != 0)
	{
		minishell->interactive = true;
		return (true);
	}
	else if (argc > 2 && ft_strncmp(argv[1], "-c", 2) == 0)
	{
		if (!argv[2] || ft_strncmp(argv[2], "$@", 3) == 0)
			exit_msg(minishell,
				"bash:-c: option requires\
						an argument",
				2);
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
//	char		*readline_input;
//	char		**arg_input;
//	int			i;
//
//	if (ac > 2 && !av[2])
//	{
//		ft_putendl_fd("bash: -c: option requires an argument", 2);
//		exit(2);
//	}
//	ft_bzero(&minishell, (sizeof(t_minishell)));
//	minishell.total_commands = 1;
//	set_minishell_paths(&minishell);
//	set_environment(&minishell, envp);
//	if (ac == 3 && ft_strcmp(av[1], "-c") == 0 && av[2])
//	{
//		if (!av[2])
//		{
//			ft_putendl_fd("bash: -c: option requires an argument", 2);
//			exit(2);
//		}
//		arg_input = ft_split(av[2], ';');
//		if (!arg_input)
//			return (1);
//		i = 0;
//		while (arg_input[i])
//		{
//			minishell_non_interactive(&minishell, arg_input[i]);
//			init_before_next_prompt(&minishell);
//			i++;
//		}
//	}
//	else
//	{
//		while (1)
//		{
//			readline_input = readline(PROMPT);
//			minishell_non_interactive(&minishell, readline_input);
//			init_before_next_prompt(&minishell);
//		}
//	}
//	if (0 && is_interactive(&minishell, ac, av) == true)
//		minishell_interactive(&minishell);
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
	free_minishell(&minishell);
	return (minishell.status);
}
