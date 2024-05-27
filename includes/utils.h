/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:25:33 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/24 22:09:44 by mbernard         ###   ########.fr       */
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

/******************** FREE ********************/

void			free_token(t_token_list *token);
void			free_minishell(t_minishell *minishell);
void			ft_free_tab(char ***tab);
void			ft_lstclear_envp(t_envp_list **lst);
void			ft_lstclear_token(t_token_list **lst);
void			ft_free_process_list(t_process_list **process_list);
void			check_and_delete_if_tmp_file_exists(char *tmp_file);
/*** FREE  UTILS *****/
void			free_strs(t_minishell *m);
void			close_all_fds(t_minishell *m, t_process_list *pl);
void			free_safely_str(char **str_to_free);

/******************** ERROR ********************/
void			print_error(const char *error);
bool			print_operator_syntax_error(t_token_list *token);
void			print_cmd_perror(char *cmd, char *name, int err);
void			print_cmd_perror_no_strerror(char *cmd, char *name);
void			exit_msg(t_minishell *m, char *msg, int error_code);

/******************** TOKEN LIST *****************/
int				ft_lstsize_token(t_token_list *lst);
t_token_list	*ft_lstlast_token(t_token_list *lst);
void			add_token_to_list(t_token_list **list_tokens,
					t_token_list *new_token);

/******************** ENV UTILS *****************/
void			set_current_path_with_cwd(t_minishell *m);
bool			set_env_var(t_minishell *m, char **var, char *target);
void			set_minishell_paths(t_minishell *m);
void			increment_shell_level(t_envp_list **env_vars, t_minishell *m);

#endif // UTILS_H
