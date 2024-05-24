/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:43:37 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/19 09:43:37 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include "parser.h"


void	free_envp(t_envp_list *envp)
{
	if (envp != NULL)
	{
		free_safely_str(&(envp->target));
		free_safely_str(&(envp->value));
		free(envp);
		envp = NULL;
	}
}

void	free_all(char *value, char *key)
{
	free_safely_str(&value);
	free_safely_str(&key);
}
