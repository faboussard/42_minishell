/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:01:29 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/04 08:54:08 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

# ifndef READ_END
#  define READ_END 0
# endif

# ifndef WRITE_END
#  define WRITE_END 1
# endif

//---------------------------- SAFE UTILS -----------------------------//
pid_t	m_safe_fork(t_minishell *minishell);
void	m_safe_dup2(t_minishell *minishell, int old_fd, int new_fd);
bool	safe_pipe(t_minishell *m);
void	close_pipes(int *pipe_fd);
void	close_fds(int fd_in, int fd_out);
void	check_and_delete_if_tmp_file_exists(char *tmp_file);
//--------------------------- PATHS -----------------------------------//
void	set_paths(t_minishell *m, char **env);
void	set_good_path_cmd(t_minishell *m, t_process_list *pl, char *cmd);
char	*join_sep(t_minishell *m, char *s1, char *s2, char sep);
//--------------------------- FD MANAGEMENT ---------------------------//
void	open_fd_infile(t_minishell *m, t_token_list *in_files_list);
void	open_fd_outfile(t_minishell *m, char *out);
//--------------------------- HERE_DOC --------------------------------//
void	here_doc(t_minishell *m, char *limiter);
//--------------------------- UTILS -----------------------------------//
void	ft_free_tab(char **tab);
void	ft_init_process_list_and_minishell(t_minishell *m, t_process_list *pl);
void	ft_free_node_process_list(t_minishell *m, t_process_list *pl);
//--------------------------- CHILD CARE ------------------------------//
void	exec_several_cmds(t_minishell *m, t_process_list *process_list);
//--------------------------- EXEC ------------------------------------//
void	my_execve(t_minishell *m, t_process_list *pl);
//void	my_execve(char **cmd_table, char **env, t_minishell *m);
//void	execute_cmds(t_minishell *minishell, int nb_cmds);
//--------------------------- ERRORS ------------------------------------//
void	print_name(t_minishell *m, char *name);
void	exit_command_not_found(t_minishell *m, char *name);
void	exit_msg_minishell(t_minishell *m, char *msg, int error_code);
void	print_name_and_exit_perror(t_minishell *m, char *name, int error_code);
void	print_name_and_exit_msg(t_minishell *m, char *name, char *msg, int err);
void	print_name_and_give_status(t_minishell *m, char *name, int err);
void	malloc_error_with_exit(t_minishell *m);
void	malloc_error_no_exit(t_minishell *m);
#endif