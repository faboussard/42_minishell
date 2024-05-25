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

void ignore_signals()
{
	ignore_sigquit();
	ignore_sigint();
}

void	sigint_handler_heredoc(int signo)
{
	(void)signo;
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
	exit(130);
}

int set_signals_heredoc()
{
	struct sigaction	action;

	ignore_sigquit();
	action.sa_handler = &sigint_handler_heredoc;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &action, NULL) < 0)
	{
		print_error("sigaction() failed");
		return (-1);
	}
	return (0);
}

