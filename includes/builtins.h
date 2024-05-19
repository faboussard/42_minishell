/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/07 08:50:20 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H


# include "utils.h"


//----------------------------------BUILTINS----------------------------------//
int		ft_exit(t_minishell *minishell, char **cmd_table);
int		ft_env(t_minishell *minishell, char **args);
int		ft_cd(t_minishell *m, char **cmd_table);
int		ft_echo(char **cmd_table);
int		ft_pwd(t_minishell *minishell);
int ft_export(char **args, t_envp_list **env_variables, t_minishell *m);
int export_variables(char **args, t_envp_list *env_variables, t_minishell *m);
int		ft_unset(t_minishell *minishell, char **args);

//-------------------------------BUILTINS UTILS-------------------------------//
char	*ft_realpath(t_minishell *m, char *dir);
bool	contains_only_charset(const char *str, const char *charset);
int		ft_atoi_long(const char *str, bool *error);
bool	is_valid_env_var_key(char *var);
void action_for_no_valid_key(char *arg, bool *check_key);
bool is_valid_key_with_plus(char *key);
bool join_with_old(t_envp_list **cpy, char *value);
char *join_new_value_env_with_old(t_envp_list **envp, char *value);
void process_argument_with_equal_sign(t_minishell *m, t_envp_list *env, char *value, char *key);
void process_no_equal_sign(char *arg, t_minishell *m, bool *check_key);

//void	clear_path_char(char str[PATH_MAX]);

#endif // BUILTINS_H