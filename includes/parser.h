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

#include "libft.h"
#include "minishell.h"

/************************** parser  **************************/

char **split_user_input(t_minishell *minishell);
int parse_input(t_minishell *minishell);
void	token_requalification(t_token_list *list_tokens);
int check_syntax(t_minishell *minishell);

/**************************** count tokens **************************/

size_t	count_letters_until_pipe_or_redirect(t_token_list *head);
size_t	count_cmds_until_pipe_or_redirect(t_token_list *head);

/**************************** parse tokens **************************/

void	create_process_list(t_minishell *minishell);
t_process_list	*create_process_list_node(t_process_list *new_process_list, t_minishell *minishell);
void	create_envp_table(t_minishell *minishell);
void	add_token_to_list(t_token_list **list_tokens, t_token_list *new_token);

/****************** OPERATORS ******************/

bool	get_operator_token(t_token_list *new_token, char *string);
bool	is_redirect_token(t_token_list *token);

/******************** init.c **********************/
void	parsing(t_minishell *minishell, int ac, char **av, char **envp);

/********************* envp.c **************************/
t_envp_list	*create_envp_list(char **envp, t_minishell *minishell);

/********************* expansion.c ****************************/
void expand_and_create_envp_table(t_minishell *minishell);

#endif //PARSER_H
