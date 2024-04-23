/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/19 11:06:17 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "utils.h"
#include <stdlib.h>


void	token_requalification(t_minishell *minishell, t_token_list *list_tokens)
{
	if (list_tokens)
	{
		to_infile_or_outfile(list_tokens);
		arg_to_command(list_tokens);
		define_builtins(list_tokens);
		define_operators(list_tokens);
		define_heredoc_and_append(minishell, &minishell->list_tokens);
	}
}
