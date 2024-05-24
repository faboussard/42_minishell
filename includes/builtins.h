/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/24 22:01:08 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "utils.h"

# define PWD_ER \
	"cd: error retrieving current directory: \
getcwd: cannot access parent directories"

//----------------------------------BUILTINS----------------------------------//
int		ft_exit(t_minishell *minishell, char **cmd_table);
int		ft_env(t_minishell *minishell, char **args);
int		ft_cd(t_minishell *m, char **cmd_table);
int		ft_echo(char **cmd_table);
int		ft_pwd(t_minishell *minishell);
int		ft_export(char **args, t_envp_list **env_variables, t_minishell *m);
int		make_export(char **args, t_envp_list *env_variables, t_minishell *m);
int		ft_unset(t_minishell *minishell, char **args);

//-------------------------------BUILTINS UTILS-------------------------------//
char	*ft_realpath(t_minishell *m, char *dir);
bool	ft_getenv(t_minishell *m, char dest[PATH_MAX], char *key);
bool	should_go_home(char **cmd_table);
bool	contains_only_charset(const char *str, const char *charset);
int		ft_atoi_long(const char *str, bool *error);
bool	is_valid_env_var_key(char *var);
void	print_error_export(char *arg, bool *check_key);
bool	is_valid_key_with_plus(char *key);

char	*join_with_old(t_envp_list **list, char *content, t_minishell *m);
void	add_to_env(t_minishell *m, t_envp_list *env, char *value, char *key);
char	*find_and_join_value(const char *key, t_envp_list **head, char *value,
			t_minishell *m);
int		ascending(char *a, char *b);

#endif // BUILTINS_H
