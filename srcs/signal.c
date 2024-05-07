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

int	set_or_get_last_status(int status, int flag)
{
	static int	last_status;

	if (flag == 0)
		last_status = status;
	return (last_status);
}

void	sigint_handler(int signo)
{
//	if (WIFEXITED(signo))
//		set_or_get_last_status(WEXITSTATUS(signo) + 128, 0);
//	if (WIFSIGNALED(signo))
//		set_or_get_last_status(WTERMSIG(signo) + 128, 0);
//	if (WIFSTOPPED(signo))
//		set_or_get_last_status(WSTOPSIG(signo) + 128, 0);
////		set_or_get_last_status(131, 0);
//	dprintf(2, "Quit: 3\n");
	set_or_get_last_status(130, 0);
	(void)signo;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
//	set_or_get_last_status(130, 0);
//	printf("\n");
//	rl_on_new_line();
//	rl_replace_line("", 0);
//	rl_redisplay();
}

//void sigquit_handler(int signo)
//{
//	(void)signo;
//}

void	set_signals_interactive()
{
	struct sigaction	action;

	action.sa_handler = (__sighandler_t) sigint_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	if (sigaction(SIGINT, &action, NULL) < 0)
	{
		print_error("sigaction() failed");
		return ;

	}
	action.sa_handler = SIG_IGN; // Ignorer Ctrl + '\'
    if (sigaction(SIGQUIT, &action, NULL) < 0)
	{
		perror("sigaction() failed");
		return ;
	}
	signal(SIGTSTP, SIG_IGN);
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
