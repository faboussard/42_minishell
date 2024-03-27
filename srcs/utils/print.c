/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:43:37 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/19 09:43:37 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

void print_array(char **array)
{
    printf("------------------- PRINT ARRAY ------------------------------------\n");
	int i;

	if (array == NULL)
	{
        printf("no array to print\n");
		return;
	}
	i = 0;
	while (array[i] != NULL)
	{
        printf("%s\n", array[i]);
		i++;
	}
}

void print_token_list(t_node *list_tokens)
{
	t_node  *iterator;
	t_token *token;

	if (list_tokens == NULL)
	{
        printf("no list to  print\n");
		return;
	}
    printf("----------------------- PRINT LIST -----------------------\n");
	iterator = list_tokens;
	while (iterator != NULL)
	{
		token = (t_token *)(iterator)->content;
        printf("Name : %s, Type: %d, Builtin: %d, Operator: %d\n", token->name, token->e_type, token->e_builtin, token->e_operator);
		iterator = iterator->next;
	}
    printf("\n");
}

void print_list_envp(t_minishell *minishell)
{
    t_node *current;
    t_envp_content *envp_content;

    if (minishell->list_envp == NULL)
    {
        printf("no list to print\n");
        return;
    }
    printf("----------------------- PRINT LIST -----------------------\n");
    current = minishell->list_envp;
    while (current != NULL)
    {
        envp_content = (t_envp_content *)(current)->content;
        printf("Target: %s, Value: %s\n", envp_content->target, envp_content->value);
        current = current->next;
    }

    printf("\n");
}