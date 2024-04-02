/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                            		    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/22 12:10:15 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define MALLOC_FAILED (-1)
#define SUCCESSFULLY_ADDED 0

#include "libft.h"
#include "lexer.h"
#include "minishell.h"
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_envp	t_envp;
typedef struct s_token  t_token;
typedef struct s_minishell t_minishell;
typedef struct process_list t_process_list;
typedef struct in_out_files_tokens t_in_out_files_tokens;
typedef struct limiter_tokens t_limiter_tokens;

typedef struct s_minishell
{
	bool				interactive;
	pid_t				pid1;
	pid_t				pid2;
	int					status;
	int					pipe_fd[2];
	int					fd_in;
	int					fd_out;
	int 				history_count;
	char				*user_input;
	char 				**envp_table;
	t_token		        *list_tokens;
	t_envp		        *list_envp;
	t_process_list		*process_list;
	size_t              total_commands;
	size_t				total_size_envp;
}	t_minishell;

typedef struct s_envp
{
	char			*value;
	char			*target;
	size_t 			value_size;
	size_t 			target_size;
	struct s_envp 	*next;
}	t_envp;

typedef struct process_list
{
	char 	**cmd_table;
	t_token *tokens_until_pipe;
	t_token	*in_files_list;
	t_token	*out_files_list;
	t_token	*limiters;
	struct	process_list	*next;
} t_process_list;

/*************************************** INIT MINISHELL ***************************************/

void	ft_init_minishell(t_minishell *minishell, int ac, char **av);
bool	is_interactive(t_minishell *minishell, int ac);
t_token	*parse_input(t_minishell *minishell);

/*************************************** CREATE CHAINS ***************************************/

void	create_token_chain_list(t_minishell *minishell, char *string);
void	create_envp_hashmap(t_minishell *minishell, char **envp);

/*************************************** CREATE TABLES ***************************************/

void	create_tables(t_minishell *minishell);

#endif