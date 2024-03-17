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

#include "libft.h"

typedef struct s_minishell
{
	t_hashmap		hm_env_variables;
	t_node			*list_tokens;
	t_node			*list_here_docs;
}	t_minishell;

#endif