/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/05 11:17:13 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "minishell.h"
#include "signals.h"
#include "utils.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

void	signal_print_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
}

void	sigint_handler(int signo, t_minishell *minishell)
{
	(void)(signo);
	free_minishell(minishell);
}

void	set_signals_interactive(void)
{
	struct sigaction	action;

	ignore_sigquit();
	action.sa_handler = (void (*)(int))sigint_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	if (sigaction(SIGINT, &action, NULL) < 0)
	{
		print_error("sigaction() failed");
		return ;
	}
}

void	signal_reset_prompt(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signals_noninteractive(void)
{
	struct sigaction	action;

	ft_memset(&action, 0, sizeof(action));
	action.sa_handler = &signal_print_newline;
	sigaction(SIGINT, &action, NULL);
	if (sigaction(SIGINT, &action, NULL) < 0)
	{
		print_error("sigaction() failed");
		return ;
	}
	sigaction(SIGQUIT, &action, NULL);
	if (sigaction(SIGQUIT, &action, NULL) < 0)
	{
		print_error("sigaction() failed");
		return ;
	}
}

// interet de SIGUIT (ctrl + \ ) si on lignore ??
/*In interactive mode:
◦ ctrl-C displays a new prompt on a new line.
◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing.*/
void	ignore_sigquit(void)
{
	struct sigaction	action;

	action.sa_handler = SIG_IGN;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	if (sigaction(SIGQUIT, &action, NULL) < 0)
	{
		print_error("sigaction() failed");
		return ;
	}
}
