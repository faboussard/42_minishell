/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/24 22:19:35 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef MALLOC_FAILED
#  define MALLOC_FAILED -1
# endif

# ifndef SUCCESSFULLY_ADDED
#  define SUCCESSFULLY_ADDED 0
# endif

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# ifndef ARG_MAX
#  define ARG_MAX 2097152
# endif

# ifndef PROMPT
#  define PROMPT "\001\e[27m\002>>> \001\e[0m\e[45m\002 \
Minishell>$ \001\e[0m\002"
# endif

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include "lexer.h"
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_envp			t_envp_list;
typedef struct s_token			t_token_list;
typedef struct s_minishell		t_minishell;
typedef struct s_process_list	t_process_list;
typedef struct s_here_doc_list	t_here_doc_list;

typedef struct s_minishell
{
	bool						interactive;
	pid_t						pid1;
	pid_t						pid2;
	int							status;
	int							pipe_fd[2];
	int							tmp_in;
	char						*user_input;
	char						current_path[PATH_MAX];
	char						old_pwd[PATH_MAX];
	char						*paths;
	char						**envp_table;
	t_token_list				*list_tokens;
	t_envp_list					*list_envp;
	t_process_list				*pl;
	size_t						total_commands;
	size_t						total_size_envp;
	bool						interrupted_here_doc;
}								t_minishell;

typedef struct s_envp
{
	char						*value;
	char						*target;
	size_t						value_size;
	size_t						target_size;
	struct s_envp				*next;
}								t_envp_list;

typedef struct s_process_list
{
	t_token_list				*in_files_list;
	t_token_list				*out_files_list;
	int							fd_in;
	int							fd_out;
	char						*paths;
	char						*good_path;
	char						**tab_paths;
	char						**cmd_table;
	char						here_doc_file[28];
	bool						dev_null;
	struct s_process_list		*next;
}								t_process_list;

/********************************** CREATE TABLES ***************************/

void			execute_cmds(t_minishell *minishell, size_t nb_cmds);
int				set_or_get_last_status(int status, int flag);

#endif
