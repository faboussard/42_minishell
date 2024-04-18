/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:25:33 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/16 17:40:43 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

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

void free_token(t_token_list *token);
void			free_minishell(t_minishell *minishell);
void			ft_free_all_tab(char **tab);
void			ft_free_tab_from_i(void **tab, int j);
void			ft_lstclear_envp(t_envp_list **lst);
void			ft_lstclear_token(t_token_list **lst);
void			ft_free_process_list(t_process_list **process_list);
void			restore_terminal(t_minishell *minishell);
void			check_and_delete_if_tmp_file_exists(char *tmp_file);
void			free_strs(t_minishell *m);
void			close_all_fds(void);

/******************** ERROR ********************/
void			print_error(const char *error);
int				print_operator_syntax_error(t_token_list *token);
void			print_cmd_perror(char *cmd, char *name, int err);

/******************** TOKEN LIST *****************/
int				ft_lstsize_token(t_token_list *lst);
t_token_list	*ft_lstlast_token(t_token_list *lst);
void			add_token_to_list(t_token_list **list_tokens,
					t_token_list *new_token);

#endif // UTILS_H
