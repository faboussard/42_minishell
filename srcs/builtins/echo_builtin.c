/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/23 10:14:23 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* is_n_flag:
 *	Checks whether an arg is an -n option flag.
 *	Returns true if the arg is some variation of -n, -nnnn, -nn, etc.
 *	Returns false if it contains anything other than - and n (ex. --n -nnnm
		-n1234)
 */

#include "builtins.h"
#include "lexer.h"
#include "minishell.h"
#include "utils.h"
#include <readline/history.h>

int	check_n_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/* echo_print_args:
 *	Prints the given array of aruments to STDOUT.
 */
// Output the args, separated by spaces, terminated with a newline.
// The return status is 0 unless a write error occurs.
// If -n is specified, the trailing newline is suppressed.

/*
int	return_code;
return_code = printf("\n");
if (return_code == -1)
*/

int	ft_echo(t_token_list *command)
{
	t_token_list	*iterator;
	bool			flag;

	iterator = command;
	if (iterator->next == NULL)
	{
		if (printf("\n") == -1)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	iterator = iterator->next;
	flag = check_n_arg(iterator->name);
	if (flag == 1)
		iterator = iterator->next;
	while (iterator && iterator->e_type == ARGUMENT)
	{
		if (printf("%s", iterator->name) == -1)
			return (EXIT_FAILURE);
		iterator = iterator->next;
		if (iterator && iterator->e_type == ARGUMENT)
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
	return (EXIT_SUCCESS);
}
