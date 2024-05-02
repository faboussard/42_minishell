/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/28 15:14:04 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "minishell.h"
# include "utils.h"

//---------------------------- EXEC BUILTINS --------------------------//

void	exec_builtin(t_minishell *minishell, t_token_list *command,
			char **cmd_table);
//----------------------------------BUILTINS----------------------------------//
int		ft_exit(t_minishell *minishell, char **cmd_table);
int		ft_env(t_minishell *minishell, char **args);
int		ft_setenv(t_minishell *minishell);
int		ft_unsetenv(t_minishell *minishell);
int		ft_cd(t_minishell *minishell, char **cmd_table);
int		ft_echo(char **cmd_table);
int		ft_pwd(t_minishell *minishell);
int ft_export(char **args, t_envp_list *env_variables, t_minishell *m);
int export_variables(char **args, t_envp_list *env_variables, t_minishell *m);
int		ft_unset(t_minishell *minishell, char **args);
int		ft_atoi_long(const char *str, bool *error);
//-------------------------------BUILTINS UTILS-------------------------------//
void	ft_realpath(t_minishell *m, char *cmd);
bool	contains_only_charset(const char *str, const char *charset);

#endif // BUILTINS_H