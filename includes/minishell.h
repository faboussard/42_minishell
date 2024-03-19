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

#ifndef RUN_MINISHELLRC_H
# define RUN_MINISHELLRC_H

#include "../libft/inc/libft.h"

typedef struct s_minishell
{
	pid_t			pid1;
	pid_t			pid2;
	int				status;
	int				pipe_fd[2];
	int				fd_in;
	int				fd_out;
	t_hashmap		hm_env_variables;
	char 			**env_variables;
	t_node			*list_tokens;
	char 			**token_array;
	t_node			*list_here_docs;
}	t_minishell;

#endif