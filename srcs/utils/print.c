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


void print_process_list(t_process_list *process_list)
{
	t_process_list *current;

	if (process_list == NULL)
	{
		printf("no list to  print\n");
		return;
	}
	current = process_list;
	while (current != NULL)
	{
		printf("----------------------- CMD TABLE -----------------------\n");
		print_array(current->cmd_table);
		printf("-----------------------  IN FILES -----------------------\n");
		if (current->in_files_token == NULL)
			printf("no in_files_token\n");
		else
			print_token_list(current->in_files_token);
		printf("-----------------------  OUTFILES  -----------------------\n");
		if (current->out_files_token == NULL)
			printf("no out_files_token\n");
		else
			print_token_list(current->out_files_token);
		current = current->next;
	}
}
void print_array(char **array)
{
    printf("----------------------- ARRAY      -----------------------\n");
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

void print_token_list(t_token_list *list_tokens)
{
	t_token_list  *iterator;

	if (list_tokens == NULL)
	{
        printf("no list to  print\n");
		return;
	}
    printf("----------------------- tokens -----------------------\n");
	iterator = list_tokens;
	while (iterator != NULL)
	{
        printf("Name : %s, Type: %d, Builtin: %d, Operator: %d\n", iterator->name, iterator->e_type, iterator->e_builtin, iterator->e_operator);
		iterator = iterator->next;
	}
    printf("\n");
}

void print_list_envp(t_minishell *minishell)
{
    t_envp_list *current;

    if (minishell->list_envp == NULL)
    {
        printf("no list to print\n");
        return ;
    }
    printf("-----------------------  ENVP LIST -----------------------\n");
    current = minishell->list_envp;
    while (current != NULL)
    {
        printf("Target: %s, Value: %s\n", current->target, current->value);
        current = current->next;
    }
    printf("\n");
}