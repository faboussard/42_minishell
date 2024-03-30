/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tables.c                                    :+:      :+:    :+:   */
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

char	*ft_strdup_free(const char *s)
{
	char	*copy;

	copy = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (copy == NULL)
		return (NULL);
	ft_memcpy(copy, s, ft_strlen(s) + 1);
	return (copy);
}

int fill_cmds_and_args_array(t_token *list_tokens, char **array)
{
	size_t i;
    t_token	*iterator;

	i = 0;
    iterator = list_tokens;
    while (iterator && iterator->e_operator != PIPE)
	{
        if (iterator->e_type == COMMAND || iterator->e_type == ARGUMENT)
        {
            array[i] = ft_strdup(iterator->name);
            if (array[i] == NULL)
			{
				ft_free_all_tab(array);
				return 0;
			}
            i++;
        }
        iterator = iterator->next;
	}
	array[i] = NULL;
	return (1);
}

//< coucou > fichierEX ls  < coucou -la < coucou
//met le resultat de "ls -la" dans fichier prout
//-c "echo ls > ls -l | ls -l "
char **create_cmd_table(t_minishell *minishell)
{
	char **cmd_table;

	size_t nbr_cmds_letters_int_pipe;

    nbr_cmds_letters_int_pipe = count_letters_until_pipe(minishell->list_tokens);
	cmd_table= ft_calloc(nbr_cmds_letters_int_pipe, sizeof(char **));
	if (cmd_table == NULL)
		return (NULL);
    if (fill_cmds_and_args_array(minishell->list_tokens, cmd_table) == 0)
		exit_msg(minishell, "Malloc failed at tokenization", 2);
	return (cmd_table);
}

void create_envp_table(t_minishell *minishell)
{
    t_envp *current;
	size_t i;

	i = 0;
	minishell->envp_table = ft_calloc(minishell->total_size_envp + 1, sizeof(char **));
	if (minishell->envp_table == NULL)
		return ;
    current = minishell->list_envp;
	while (current != NULL)
	{
		minishell->envp_table[i] = ft_strjoin(current->target, current->value);
		if (minishell->envp_table[i] == NULL)
        {
            ft_free_all_tab(minishell->envp_table);
            return;
        }
        current = current->next;
		i++;
	}
	minishell->envp_table[i] = NULL;
}


