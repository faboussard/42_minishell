/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:54:57 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/25 13:56:40 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef READ_END
#  define READ_END 0
# endif

# ifndef WRITE_END
#  define WRITE_END 1
# endif

# ifndef SYNTAX_ERROR
#  define SYNTAX_ERROR "syntax error near unexpected token `\"\"'"
# endif

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;
	int		pipe_fd[2];
	int		tmp_in;
	int		fd_in;
	int		fd_out;
	char	*paths;
	char	*good_path;
	char	**tab_paths;
	char	**cmd_args;
	char	*cmd;
	bool	dev_null;
	bool	here_doc;
}			t_pipex;

///////////////////////////////////////////////////////////
//---------------------ERRORS----------------------------//
///////////////////////////////////////////////////////////
void		print_name(t_pipex *p, char *name);
void		exit_command_not_found(t_pipex *p, char *name);
void		print_name_and_exit_perror(t_pipex *p, char *name, int err);
void		print_name_and_exit_msg(t_pipex *p, char *name, char *msg, int err);
void		exit_msg(t_pipex *p, char *msg, int error_code);
///////////////////////////////////////////////////////////
//---------------------CHILD CARE------------------------//
///////////////////////////////////////////////////////////
pid_t		safe_fork(t_pipex *p);
void		safe_dup2(t_pipex *p, int old_fd, int new_fd);
void		exec(t_pipex *p, char *cmd, char **env);
void		open_and_check_fd_outfile(t_pipex *p, char *out);
void		child_care(t_pipex *p, char *cmd, char **env, int child);
///////////////////////////////////////////////////////////
//---------------------UTILS-----------------------------//
///////////////////////////////////////////////////////////
void		ft_init_struct(t_pipex *pipex);
void		ft_free_tab(char **tab);
void		ft_free_struct(t_pipex *pipex);
void		erase_spaces_in_cmd_args(t_pipex *p);
void		close_pipes(t_pipex *p);
void		check_null_cmd(int ac, char **av, int i);
///////////////////////////////////////////////////////////
//---------------------JOIN-----------------------------//
///////////////////////////////////////////////////////////
char		*join_sep(t_pipex *p, char *s1, char *s2, char sep);
///////////////////////////////////////////////////////////
//---------------------PATHS-----------------------------//
///////////////////////////////////////////////////////////
void		set_paths(t_pipex *p, char **env);
///////////////////////////////////////////////////////////
//---------------------CMDS------------------------------//
///////////////////////////////////////////////////////////
void		set_good_path_with_cmd(t_pipex *p, char *cmd);
void		set_cmd_args(t_pipex *p, char *cmd);
///////////////////////////////////////////////////////////
//---------------------HEREDOC---------------------------//
///////////////////////////////////////////////////////////
bool		is_here_doc(t_pipex *p, char *str);
void		handle_heredoc(t_pipex *p, char *limiter, int *i, int ac);
void		check_and_delete_if_tmp_file_exists(char *tmp_file);
#endif
