/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:26:23 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/22 08:45:43 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include "exec.h"

void create_(t_minishell *m)
{
	m->fake_env->target_ = ft_strdup("_=");
	if (m->fake_env->target_ == NULL)
		exit_msg_minishell(m, "Malloc failed at create_3_env_variables", -1);
	m->fake_env->content_ = ft_strdup("/usr/bin/env");
	if (m->fake_env->content_ == NULL)
		exit_msg_minishell(m, "Malloc failed at create_3_env_variables", -1);
}

void create_PWD(t_minishell *m)
{
	m->fake_env->target_PWD = ft_strdup("PWD=");
	if (m->fake_env->target_PWD == NULL)
		exit_msg_minishell(m, "Malloc failed at create_3_env_variables", -1);
	m->fake_env->content_PWD = ft_strdup("/home/faboussa");
	if (m->fake_env->content_PWD == NULL)
		exit_msg_minishell(m, "Malloc failed at create_3_env_variables", -1);
}

void create_SHLVL(t_minishell *m)
{
	char *temp;
	char *joined_equal;

	temp = ft_itoa(m->SHLVL);
	if (temp == NULL)
		exit_msg_minishell(m, "Malloc failed at create_3_env_variables", -1);
	joined_equal = ft_strjoin(temp, "=");
	free_safely_str(temp);
	m->fake_env->target_SHLVL = ft_strdup(joined_equal);
	free(joined_equal);
	if (m->fake_env->target_SHLVL == NULL)
		exit_msg_minishell(m, "Malloc failed at create_3_env_variables", -1);
	m->fake_env->content_SHLVL = ft_strdup("/usr/bin/echo");
	if (m->fake_env->content_SHLVL == NULL)
		exit_msg_minishell(m, "Malloc failed at create_3_env_variables", -1);
}

void free_fake_arrays(t_fake_env *fake_env)
{
	if (fake_env->target_ != NULL)
		free_safely_str(fake_env->target_);
	if (fake_env->content_ != NULL)
		free_safely_str(fake_env->content_);
	if (fake_env->target_PWD != NULL)
		free_safely_str(fake_env->target_PWD);
	if (fake_env->content_PWD != NULL)
		free_safely_str(fake_env->content_PWD);
	if (fake_env->target_SHLVL != NULL)
		free_safely_str(fake_env->target_SHLVL);
	if (fake_env->content_SHLVL != NULL)
		free_safely_str(fake_env->content_SHLVL);
	ft_bzero(fake_env, sizeof(t_fake_env));
	fake_env = NULL;
}

void create_3_env_variables(t_minishell *m)
{
	m->fake_env = ft_calloc(1, sizeof(t_fake_env));
	create_(m);
	create_PWD(m);
	create_SHLVL(m);
	if (add_new_envp(&m->list_envp, m->fake_env->target_, m->fake_env->content_))
		exit_msg_minishell(m, "Malloc failed at create_3_env_variables", -1);
	if (add_new_envp(&m->list_envp, m->fake_env->target_SHLVL, m->fake_env->content_SHLVL))
		exit_msg_minishell(m, "Malloc failed at create_3_env_variables", -1);
	if (add_new_envp(&m->list_envp, m->fake_env->target_PWD, m->fake_env->content_PWD))
		exit_msg_minishell(m, "Malloc failed at create_3_env_variables", -1);
	free_fake_arrays(m->fake_env);
}