/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/30 17:49:41 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

void	print_error(const char *error)
{
	if (error != NULL)
		ft_putendl_fd(error, STDERR_FILENO);
	else
		ft_putstr_fd("\n", STDERR_FILENO);
}

void	print_cmd_perror(t_minishell *m, char *cmd, char *name)
{
	char	*the_name;
	char	*the_semicolon;
	char	*the_msg;

	the_name = ft_strjoin("minishell: ", cmd);
	if (!the_name)
		exit_msg(m, "Malloc error", ENOMEM);
	the_semicolon = ft_strjoin(the_name, ": ");
	free_safely_str(&the_name);
	if (!the_semicolon)
		exit_msg(m, "Malloc error", ENOMEM);
	the_msg = ft_strjoin(the_semicolon, name);
	free_safely_str(&the_semicolon);
	if (!the_msg)
		exit_msg(m, "Malloc error", ENOMEM);
	perror(the_msg);
	free_safely_str(&the_msg);
}

void	print_cmd_perror_no_strerror(t_minishell *m, char *cmd, char *name)
{
	char	*the_name;
	char	*the_semicolon;
	char	*the_msg;
	char	*the_line_break;

	the_name = ft_strjoin("minishell: ", cmd);
	if (!the_name)
		exit_msg(m, "Malloc error", ENOMEM);
	the_semicolon = ft_strjoin(the_name, ": ");
	free_safely_str(&the_name);
	if (!the_semicolon)
		exit_msg(m, "Malloc error", ENOMEM);
	the_msg = ft_strjoin(the_semicolon, name);
	free_safely_str(&the_semicolon);
	if (!the_msg)
		exit_msg(m, "Malloc error", ENOMEM);
	the_line_break = ft_strjoin(the_msg, "\n");
	free_safely_str(&the_msg);
	if (!the_line_break)
		exit_msg(m, "Malloc error", ENOMEM);
	ft_putstr_fd(the_line_break, 2);
	free_safely_str(&the_line_break);
}
