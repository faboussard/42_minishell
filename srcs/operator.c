/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdbool.h>

bool	get_operator_token(t_token *new_token, char *string)
{
	int			i;
	const char	*operators[10] = {NULL,
		"(", ")", "|", ">", "<", "<<", ">>", "\"", "'",
	};

	i = 1;
	while (i < 9)
	{

		if (!ft_strncmp(string, operators[i], ft_strlen(string)))
		{
			define_token_types(OPERATOR, NO_BUILTIN, i, new_token);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

bool	is_redirect_token(t_token *token)
{
	if (token == NULL || token->e_type != OPERATOR)
		return (0);
	return (token->e_operator == INPUT_REDIRECT
			|| token->e_operator == OUTPUT_REDIRECT
			|| token->e_operator == HERE_DOC
			|| token->e_operator == APPEND);
}







