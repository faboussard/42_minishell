/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/19 16:16:46 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "minishell.h"
# include "utils.h"

//---------------------------- EXEC BUILTINS --------------------------//

void	exec_builtin(t_minishell *minishell, t_token_list *command);
//----------------------------------BUILTINS----------------------------------//
int		ft_exit_builtin(t_minishell *minishell, t_token_list *command);
int		ft_env(t_minishell *minishell);
int		ft_setenv(t_minishell *minishell);
int		ft_unsetenv(t_minishell *minishell);
int		ft_cd(t_minishell *minishell, t_token_list *command);
int		ft_echo(t_token_list *command);
int		ft_pwd(t_minishell *minishell);
int		ft_export(t_minishell *minishell);
int		ft_unset(t_minishell *minishell);

//-------------------------------BUILTINS UTILS-------------------------------//
bool	ft_realpath(t_minishell *m, char *cmd);
bool	contains_only_charset(const char *str, const char *charset);

#endif // BUILTINS_H