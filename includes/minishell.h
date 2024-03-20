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

typedef t_node**	t_dict;

typedef struct s_minishell
{
	pid_t			pid1;
	pid_t			pid2;
	int				status;
	int				pipe_fd[2];
	int				fd_in;
	int				fd_out;
	t_node			*list_tokens;
	t_dict			dict_environment;
	char 			**cmd_table;
	char 			**envp_table;
}	t_minishell;


/*************************************** CREATE TABLES ***************************************/

void create_redirect_table(t_minishell *minishell, t_node **list_tokens);

#endif