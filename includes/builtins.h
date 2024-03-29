/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h             			                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/22 12:10:15 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_BUILTINS_H
#define MINISHELL_BUILTINS_H

#include "libft.h"
#include "minishell.h"


int	ft_exit_builtin(t_minishell *minishell);
int	ft_env(t_minishell *minishell);
int	ft_setenv(t_minishell *minishell);
int	ft_unsetenv(t_minishell *minishell);
int	ft_cd(t_minishell *minishell);
int	ft_echo(t_minishell *minishell);
int	ft_pwd(t_minishell *minishell);
int	ft_export(t_minishell *minishell);
int	ft_unset(t_minishell *minishell);

#endif //MINISHELL_BUILTINS_H
