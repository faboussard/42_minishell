/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/09 22:13:07 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include <stdlib.h>

int tokenize_input(t_minishell *m, char *string)
{
	transform_to_token(m, string, &m->list_tokens);
	if (m->list_tokens == NULL)
		return (0);
	define_heredoc_and_append(m, &m->list_tokens);
	return (1);
}

int requalify_tokens(t_token_list *list_tokens)
{
	if (list_tokens == NULL)
		return (0);
	to_infile_or_outfile(list_tokens);
	arg_to_command(list_tokens);
	define_builtins(list_tokens);
	define_operators(list_tokens);
	return (1);
}


int rework_tokens(t_minishell *m)
{
	token_rework(m);
	return (m->list_tokens != NULL);
}

void create_environment_table(t_minishell *m)
{
	create_envp_table(m);
}

int parse_input(t_minishell *m)
{
	if (m->list_envp == NULL)
		return (1);
	if (!tokenize_input(m, m->user_input))
		return (0);
	if (check_quotes(m))
		return (1);
	expander(m, &m->list_tokens);
	if (!rework_tokens(m))
		return (0);
	if (check_syntax(m) == 1)
	{
		m->status = set_or_get_last_status(2, 0);
		return (1);
	}
	if (!requalify_tokens(m->list_tokens))
		return (1);
	create_environment_table(m);
	create_process_list(m, &m->pl);
	m->total_commands += count_tokens_by_operator(m, PIPE);
	return (0);
}

