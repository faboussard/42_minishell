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
#include "utils.h"
#include <stdlib.h>

int tokenize_input(t_minishell *m, char *string)
{
	transform_to_token(m, string, &m->list_tokens);
	if (m->list_tokens == NULL)
		return (0);
	define_heredoc_and_append(m, &m->list_tokens);
	return (1);
}


void	redefine_empty_command(t_minishell *m, t_token_list *list_tokens)
{
	t_token_list	*iterator;
	char *new_list_name;

	iterator = list_tokens;
	if (ft_strncmp(iterator->name, "\0", 1) == 0)
		change_token_name(m, &list_tokens, "''");
	while (iterator && iterator->next != NULL)
	{
		if (iterator->e_type != COMMAND && !is_redirect_token(iterator) && ft_strncmp(iterator->next->name, "\0", 1) == 0)
		{
			iterator = iterator->next;
			new_list_name = ft_strdup("''");
			if (new_list_name == NULL)
				exit_msg(m, "Malloc failed at join between spaces", ENOMEM);
			free_safely_str(&(iterator->name));
			iterator->name = new_list_name;
		}
		iterator = iterator->next;
	}
}

int requalify_tokens(t_token_list *list_tokens, t_minishell *m)
{
	if (list_tokens == NULL)
		return (0);
	define_builtins(list_tokens);
	define_operators(list_tokens);
	to_infile_or_outfile(list_tokens);
	arg_to_command(list_tokens);
	dollar_to_command(list_tokens);
	redefine_empty_command(m, list_tokens);
	return (1);
}


int rework_tokens(t_minishell *m)
{
	token_rework(m);
	return (m->list_tokens != NULL);
}

int parse_input(t_minishell *m)
{
	if (m->list_envp == NULL)
		return (1);
	if (!tokenize_input(m, m->user_input))
		return (0);
	if (check_quotes(m))
		return (1);
	expander(m, &m->list_tokens, 0);
	if (!rework_tokens(m))
		return (0);
	if (check_syntax(m) == 1)
	{
		m->status = set_or_get_last_status(2, 0);
		return (1);
	}
	if (!requalify_tokens(m->list_tokens, m))
		return (1);
	create_process_list(m, &m->pl);
	create_envp_table(m);
	m->total_commands += count_tokens_by_operator(m, PIPE);
	return (0);
}

