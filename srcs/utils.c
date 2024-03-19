/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:43:37 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/19 09:43:37 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../libft/inc/libft.h"
#include "minishell.h"


void	ft_init_minishell(t_minishell *minishell)
{
	ft_bzero(minishell, (sizeof * minishell));
	minishell->status = 0;
	minishell->fd_in = -1;
	minishell->fd_out = -1;
}

void	exit_msg(t_minishell *minishell, char *msg, int error_code)
{
	if (minishell != NULL)
		free_minishell(minishell);
	ft_putendl_fd(msg, 2);
	exit(error_code);
}

t_token *return_last_token(t_node *list_tokens)
{
	t_node *iterator;
	t_token *last_token;

	iterator = list_tokens;
	while (iterator->next != NULL)
		iterator = iterator->next;
	last_token = (t_token *) (iterator)->content;
	return (last_token);
}

int count_tokens_until_pipe(t_node *head)
{
	int num_commands;
	t_node *current;
	t_token *token;

	num_commands = 0;
	current = head;
	while (current)
	{
		token = (t_token *) (current)->content;
		if (token->e_operator != PIPE)
			num_commands++;
		current = current->next;
	}
	return (num_commands);
}

//char **tokens_to_argv(t_node *list_tokens)
//{
//	int		count;
//	t_node	*current;
//	int		i;
//	int 	j;
//	char	**argv;
//	t_token *token;
//	int args_num_per_command;
//
//	count = ft_lstsize(list_tokens);
//	argv = malloc((count + 1) * sizeof(char **));
//	if (argv == NULL)
//		return (NULL);
//	current = list_tokens;
//
//	i = 0;
//	j = 0;
//	args_num_per_command = count_tokens_until_pipe(list_tokens);
//	while (current)
//	{
//			token = (t_token *) (current)->content;
//			argv[i] = malloc((args_num_per_command + 1) * sizeof(char *));
//			while (current && token->e_operator != OPERATOR)
//			{
//				argv[i][j] = token->name;
//				current = current->next;
//				j++;
//			}
//		}
//
//	argv[i] = NULL; // NULL terminateur pour execve
//	return (argv);
//}


