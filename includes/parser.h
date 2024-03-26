/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                               		    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/22 12:10:15 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "../libft/inc/libft.h"
#include "minishell.h"

/************************** parser  **************************/

void	token_rework(t_node *list_tokens);

/**************************** count tokens **************************/

size_t	count_letters_until_pipe_or_redirect(t_node *head);
size_t	count_cmds_until_pipe_or_redirect(t_node *head);
size_t	calculate_total_size(t_hashmap_struct *hashmap);

/**************************** parse tokens **************************/

t_hashmap_struct	*create_envp_hm(char **envp);
void				create_envp_table(t_minishell *minishell, t_hashmap_struct **hashmap);
void				create_cmd_table(t_minishell *minishell, t_node *list_tokens);

/****************** OPERATORS ******************/

bool	get_operator_token(t_token *new_token, char *string);
bool	is_redirect_token(t_token *token);
void	print_operator_syntax_error(t_token *token);

/******************** init.c **********************/
void	parsing(t_minishell *minishell, int ac, char **av, char **envp);

#endif //PARSER_H
