/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:25:33 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/13 16:30:16 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef GENERAL_H
# define GENERAL_H

enum e_bool
{
	FALSE = 0,
	TRUE = 1,
};

/******************** UTILS ********************/

t_token	*return_last_token(t_node *list_tokens);
void	ft_init_minishell(t_minishell *minishell);
void	exit_msg(t_minishell *minishell, char *msg, int error_code);
void	fill_array(t_node **list_tokens, char **array, int cmd_until_pipe);

/******************** PRINT ********************/

void	print_token(t_node *list_tokens);
void	print_array(char **array);
void	print_envp_dict(t_dict envp_dict);

/******************** FREE ********************/

void	free_minishell(t_minishell *minishell);
void	ft_free_double_tab(char **tab);
void	ft_free_tab_from_i(void **tab, int j);
void	free_token(t_token	*token);
void	free_dict(t_dict_content *dict);

#endif //GENERAL_H
