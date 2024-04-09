/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:25:33 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/04 16:19:47 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef GENERAL_H
# define GENERAL_H

enum			e_bool
{
	FALSE = 0,
	TRUE = 1,
};

/******************** UTILS ********************/

t_token_list	*return_last_token(t_token_list *list_tokens);
void			exit_msg(t_minishell *minishell, char *msg, int error_code);

/******************** PRINT ********************/

void			print_token_list(t_token_list *list_tokens);
void			print_array(char **array);
void			print_list_envp(t_minishell *minishell);
void			print_process_list(t_process_list *process_list);

/******************** FREE ********************/

void			free_minishell(t_minishell *minishell);
void			ft_free_all_tab(char **tab);
void			ft_free_tab_from_i(void **tab, int j);
void			ft_lstclear_envp(t_envp_list **lst);
void			ft_lstclear_token(t_token_list **lst);
void			ft_free_process_list(t_process_list **process_list);
void restore_terminal(t_minishell *minishell);

/******************** ERROR ********************/
void			print_error(const char *error);
int				print_operator_syntax_error(t_token_list *token);


/******************** TOKEN LIST *****************/
int	ft_lstsize_token(t_token_list *lst);
t_token_list	*ft_lstlast_token(t_token_list *lst);
void add_token_to_list(t_token_list **list_tokens, t_token_list *new_token);

#endif // GENERAL_H
