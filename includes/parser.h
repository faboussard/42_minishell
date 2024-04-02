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

void	token_requalification(t_token *list_tokens);
int     check_syntax(t_token *list_tokens);

/**************************** count tokens **************************/

size_t	count_letters_until_pipe_or_redirect(t_token *head);
size_t	count_cmds_until_pipe_or_redirect(t_token *head);

/**************************** parse tokens **************************/

t_process_list *create_process_list(t_minishell *minishell, t_token *list_tokens);
char	**create_cmd_table(t_minishell *minishell);
void create_envp_table(t_minishell *minishell);
void add_token_to_list(t_token **list_tokens, t_token *new_token);

/****************** OPERATORS ******************/

bool	get_operator_token(t_token *new_token, char *string);
bool	is_redirect_token(t_token *token);

/******************** init.c **********************/
void	parsing(t_minishell *minishell, int ac, char **av, char **envp);

/********************* envp.c **************************/
t_envp	*create_envp_list(char **envp, t_minishell *minishell);

#endif //PARSER_H
