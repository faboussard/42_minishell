/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:36:07 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/24 15:38:27 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"

int	fill_env_value_and_current_path(t_minishell *m, t_envp_list *env, char *cwd)
{
	size_t	curpath_len;
	size_t	cwd_len;

	curpath_len = ft_strlen(m->current_path) + 1;
	cwd_len = ft_strlen(cwd) + 1;
	ft_strlcpy(m->old_pwd, m->current_path, curpath_len);
	ft_strlcpy(m->current_path, cwd, cwd_len);
	free_safely_str(&(env->value));
	env->value = ft_strdup(cwd);
	if (env->value == NULL)
	{
		ft_putstr_fd("Malloc error in cd : fill_env_value_and_path\n", 2);
		return (ENOMEM);
	}
	return (0);
}

int	change_pwd_variable(t_minishell *m, char *str)
{
	t_envp_list	*env;
	char		cwd[PATH_MAX];

	env = m->list_envp;
	while (env && env->target)
	{
		if (ft_strncmp(env->target, "PWD=", 4) == 0)
			return (fill_env_value_and_current_path(m, env, str));
		env = env->next;
	}
	if (!env)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror(PWD_ER);
			return (-1);
		}
		return (fill_env_value_and_current_path(m, env, cwd));
	}
	return (1);
}

static int	go_into_directory(t_minishell *m, char *dir)
{
	char	cwd[PATH_MAX];
	char	*target_path;

	target_path = ft_realpath(m, dir);
	if (target_path == NULL)
	{
		ft_putstr_fd("Malloc error in cd : go_into_directory\n", 2);
		return (ENOMEM);
	}
	if (chdir(target_path) != 0)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			free_safely_str(&target_path);
			perror(PWD_ER);
			return (0);
		}
		print_cmd_perror(m, "cd", dir);
		free_safely_str(&target_path);
		return (1);
	}
	if (ft_strncmp(dir, ".", 2) != 0)
		change_pwd_variable(m, target_path);
	free_safely_str(&target_path);
	return (0);
}

static int	get_home(t_minishell *m)
{
	size_t	home_dir_len;
	int		return_value;
	char	dir_cpy[PATH_MAX];

	dir_cpy[0] = '\0';
	if (ft_getenv(m, dir_cpy, "HOME=") == 0)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	home_dir_len = ft_strlen(dir_cpy);
	ft_strlcat(dir_cpy, "/", home_dir_len + 1);
	return_value = go_into_directory(m, dir_cpy);
	return (return_value);
}

int	ft_cd(t_minishell *m, char **cmd_table)
{
	char	*dir;

	if (cmd_table[1] != NULL && cmd_table[2] != NULL)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (should_go_home(cmd_table))
		return (get_home(m));
	if (contains_only_charset(cmd_table[1], "/"))
		return (go_into_directory(m, "/"));
	dir = cmd_table[1];
	if (ft_strncmp(dir, "-", 2) == 0)
		return (go_into_directory(m, m->old_pwd));
	return (go_into_directory(m, dir));
}
