/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:43:37 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/06 10:07:34 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

void	print_process_list(t_process_list *process_list)
{
	t_process_list	*current;

	if (process_list == NULL)
	{
		printf("no list to  print\n");
		return ;
	}
	current = process_list;
	while (current != NULL)
	{
		printf("----------------------- CMD TABLE -----------------------\n");
		print_array(current->cmd_table);
		printf("-----------------------  IN FILES -----------------------\n");
		if (current->in_files_list == NULL)
			printf("no in_files_list\n");
		else
			print_token_list(current->in_files_list);
		printf("-----------------------  OUTFILES  -----------------------\n");
		if (current->out_files_list == NULL)
			printf("no out_files_list\n");
		else
			print_token_list(current->out_files_list);
		current = current->next;
	}
}

void	print_array(char **array)
{
	int	i;

	if (array == NULL)
	{
		printf("no array to print\n");
		return ;
	}
	i = 0;
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}

void	print_token_list(t_token_list *list_tokens)
{
	t_token_list	*iterator;

	if (list_tokens == NULL)
	{
		printf("no list to  print\n");
		return ;
	}
	printf("----------------------- tokens -----------------------\n");
	iterator = list_tokens;
	while (iterator != NULL)
	{
		printf("Name : %s, Type: %d, Builtin: %d, Operator: %d\n",
			iterator->name, iterator->e_type, iterator->e_builtin,
			iterator->e_operator);
		iterator = iterator->next;
	}
	printf("\n");
}

void	print_list_envp(t_minishell *minishell)
{
	t_envp_list	*current;

	current = minishell->list_envp;
	while (current != NULL)
	{
		printf("%s%s\n", current->target, current->value);
		current = current->next;
	}
}

void	ft_print_minishell(t_minishell *minishell)
{
	printf("************ print list_envp ************\n\n");
	print_list_envp(minishell);
	printf("************ print list_tokens ************\n");
	print_token_list(minishell->list_tokens);
	printf("************ process list (cmd table ,in out files,limiters\
			: ********* \n");
	print_process_list(minishell->pl);
	printf("********************** print env_table**********************\n\n");
	print_array(minishell->envp_table);
}
