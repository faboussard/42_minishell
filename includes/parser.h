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

/**************************** count tokens **************************/

int count_tokens_until_pipe_or_redirect(t_node *head);
int count_tokens_from_in_redirect(t_node *head);
int count_tokens_from_out_redirect(t_node *head);

/**************************** parse tokens **************************/

void create_envp_table(t_minishell *minishell, t_dict envp_dict);
void create_cmd_table(t_minishell *minishell, t_node **list_tokens);

/****************** OPERATORS ******************/

bool	get_operator_token(t_token *new_token, char *string);
bool	is_redirect_token(t_token *token);
void	print_operator_syntax_error(t_token *token);

/**************************** parser **************************/



#endif //PARSER_H
