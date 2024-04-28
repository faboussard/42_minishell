/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:01:29 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/29 09:29:53 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

//---------------------------- SAFE UTILS -----------------------------//
pid_t	m_safe_fork(t_minishell *minishell);
void	m_safe_dup2(t_minishell *minishell, int old_fd, int new_fd);
void	close_pipes(int *pipe_fd);
void	close_fds(int fd_in, int fd_out);
void	check_and_delete_if_tmp_file_exists(char *tmp_file);
//--------------------------- FD MANAGEMENT ---------------------------//
void	open_fd_infile(t_minishell *m, char *in);
void	open_fd_outfile(t_minishell *m, char *out, bool trunk_or_append);
//--------------------------- FD MANAGEMENT ---------------------------//
void	here_doc(t_minishell *m, char *limiter);
#endif
