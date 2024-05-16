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

void	sigint_handler_interrupt(int signo)
{
	(void)signo;
	set_or_get_last_status(130, 0);
}

void	sigquit_handler_interrupt(int signo)
{
	(void)signo;
	ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	set_or_get_last_status(131, 0);
}

int signal_interrupt()
{
	struct sigaction	action;

	action.sa_handler = &sigint_handler_interrupt;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &action, NULL) < 0)
	{
		print_error("sigaction() failed");
		return (-1);
	}
	action.sa_handler = &sigquit_handler_interrupt;
	if (sigaction(SIGQUIT, &action, NULL) < 0)
	{
		print_error("sigaction() failed");
		return (-1);
	}
	return (0);
}