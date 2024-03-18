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
}	e_bool;

t_token	*return_last_token(t_node *list_tokens);
void	print_token(t_node *list_tokens);
void	create_double_array(t_minishell *minishell, t_node *list_tokens);

/******************** FREE ********************/

void	free_minishell(t_minishell *minishell);
void	ft_free_double_tab(char **tab);
void	ft_free_tab_from_i(void **tab, int j);

#endif //GENERAL_H
