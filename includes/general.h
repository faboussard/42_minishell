/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                            		        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/22 12:10:15 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_GENERAL_H
#define MINISHELL_GENERAL_H

typedef enum
{
	FALSE = 0,
	TRUE = 1,
} e_bool;

void	ft_free_split(char **tab);
void	ft_free_tab(void **tab, int j);

#endif //MINISHELL_GENERAL_H
