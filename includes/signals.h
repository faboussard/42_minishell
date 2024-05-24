/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/17 23:05:40 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

int		set_signals_interactive(void);
void	signal_print_newline(int signal);
int		set_signals_noninteractive(void);
void	manage_interrupted_signal(t_minishell *m);
int		signal_interrupt(void);
int		set_signals_heredoc(void);
void	ignore_sigint(void);
void	ignore_sigquit(void);
void	ignore_signals(void);

#endif // SIGNALS_H
