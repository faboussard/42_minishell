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

void	token_rework(t_node *list_tokens);

/**************************** count tokens **************************/

int count_tokens_until_pipe_or_redirect(t_node *head);
int count_tokens_from_in_redirect(t_node *head);
int count_tokens_from_out_redirect(t_node *head);


#endif //PARSER_H
