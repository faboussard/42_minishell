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

#include "../libft/inc/libft.h"
#include "lexer.h"
#include "minishell.h"
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef t_node**	t_dict;

typedef struct s_hashmap
{
	t_dict 				dict_chain;
	size_t				total_size;
	char 				**target_tab;
}	t_hashmap_struct;

typedef struct s_minishell
{
	bool				interactive;
	pid_t				pid1;
	pid_t				pid2;
	int					status;
	int					pipe_fd[2];
	int					fd_in;
	int					fd_out;
	t_node				*list_tokens;
	t_hashmap_struct	*hashmap_environment;
	char 				**cmd_table;
	char 				**envp_table;

}	t_minishell;


/*************************************** INIT MINISHELL ***************************************/

void	ft_init_minishell(t_minishell *minishell, char **envp);


/*************************************** CREATE CHAINS ***************************************/

void	create_token_chain_list(t_minishell *minishell, char *string);
void	create_envp_hashmap(t_minishell *minishell, char **envp);

/*************************************** CREATE TABLES ***************************************/

void	create_tables(t_minishell *minishell);

#endif