/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/09 22:12:19 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "utils.h"
#include <signal.h>

void	signal_print_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
}

void	sigint_handler(int signo)
{
	(void)signo;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	set_or_get_last_status(130, 0);
}

int set_signals_interactive()
{
	struct sigaction	action;

	ignore_sigquit();
	action.sa_handler = &sigint_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &action, NULL) < 0)
	{
		print_error("sigaction() failed");
		return (-1);
	}
	return (0);
}

int set_signals_noninteractive(void)
{
	struct sigaction	action;

	ft_memset(&action, 0, sizeof(action));
	action.sa_handler = &signal_print_newline;
	sigaction(SIGINT, &action, NULL);
	if (sigaction(SIGINT, &action, NULL) < 0)
	{
		print_error("sigaction() failed");
		return (-1);
	}
	sigaction(SIGQUIT, &action, NULL);
	if (sigaction(SIGQUIT, &action, NULL) < 0)
	{
		print_error("sigaction() failed");
		return (-1);
	}
	return (0);
}
