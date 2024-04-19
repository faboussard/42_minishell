/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:36:07 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/19 08:42:02 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"

int	is_root_directory(t_minishell *m)
{
	char	cwd[PATH_MAX];

	(void)m;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (-1);
	}
	if (ft_strncmp(cwd, "/", 1) == 0)
		return (1);
	else
		return (0);
}

// static int	safe_chdir(t_minishell *m, char *dir)
// {
// 	(void)m;
// 	if (chdir(dir) == -1)
// 	{
// 		print_cmd_perror("cd", dir, errno);
// 		return (1);
// 	}
// 	return (0);
// }
bool	contains_only_charset(const char *str, const char *charset)
{
	while (*str != '\0')
	{
		if (ft_strchr(charset, *str) == NULL)
			return (0);
		str++;
	}
	return (1);
}

int	fill_env_value_and_current_path(t_minishell *m, t_envp_list *env, char *cwd)
{
	free(env->value);
	env->value = ft_strdup(cwd);
	if (m->current_path != NULL)
		free(m->current_path);
	m->current_path = ft_strdup(cwd);
	if (env->value == NULL || m->current_path == NULL)
	{
		ft_putendl_fd("Malloc error", 2);
		return (ENOMEM);
	}
	dprintf(2, "env->value is %s\n", env->value);
	dprintf(2, "m->current_path is %s\n", m->current_path);
	return (0);
}

int	change_env_variable(t_minishell *m, char *var)
{
	t_envp_list	*env;
	char		cwd[PATH_MAX];
	size_t		var_len;

	env = m->list_envp;
	var_len = ft_strlen(var);
	while (env && env)
	{
		if (strncmp(env->target, var, var_len) == 0)
		{
			if (getcwd(cwd, sizeof(cwd)) == NULL)
			{
				perror("cd: error retrieving current directory: getcwd: cannot access parent directories");
				return (-1);
			}
			return (fill_env_value_and_current_path(m, env, cwd));
		}
		env = env->next;
	}
	return (0);
}
// void	replace_old_path(t_minishell *m)
// {
// 	if (m->old_path)
// 		free(m->old_path);
// 	m->old_path = ft_strdup(m->current_path);
// }
static int	go_into_directory(t_minishell *m, char *dir)
{
	char	cwd[PATH_MAX];

	if (!ft_strncmp(dir, ".", 2) && getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd: error retrieving current directory: getcwd: cannot access parent directories");
		return (-1);
	}
	free_safely_str(m->target_path);
	m->target_path = ft_realpath(m, dir);
	if (m->target_path != NULL)
	{
		if (chdir(m->target_path) != 0)
		{
			dprintf(2, "Ewww ! I can't go there you freak !%s\n",
				m->target_path);
			print_cmd_perror("cd", m->target_path, errno);
			return (1);
		}
	}
	else if (chdir(dir) != 0)
	{
		dprintf(2, "Ewww ! I can't go there you freak !%s\n", dir);
		print_cmd_perror("cd", dir, errno);
		return (1);
	}
	change_env_variable(m, "PWD=");
	dprintf(2, "m->target_path = %s\n", m->target_path);
	return (0);
}

static int	get_home(t_minishell *m)
{
	char	*home_dir;
	char	*new_path;
	size_t	home_dir_len;
	int		return_value;

	home_dir = getenv("HOME");
	if (home_dir == NULL)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (1);
	}
	home_dir_len = ft_strlen(home_dir);
	new_path = ft_calloc(1, home_dir_len + 2);
	if (new_path == NULL)
	{
		ft_putendl_fd("Malloc error", 2);
		return (ENOMEM);
	}
	ft_strlcpy(new_path, home_dir, home_dir_len + 1);
	new_path[home_dir_len] = '/';
	return_value = go_into_directory(m, new_path);
	free(new_path);
	return (return_value);
}

bool	should_go_home(t_token_list *command)
{
	if (command->next == NULL)
		return (1);
	if (ft_strncmp(command->next->name, "~", 2) == 0)
		return (1);
	if (ft_strncmp(command->next->name, "~/", 3) == 0)
		return (1);
	return (0);
}

bool	too_many_args(t_token_list *command)
{
	if (command->next != NULL && command->next->next != NULL)
	{
		if (command->next->next->e_type != ARGUMENT
			&& command->next->next->next == NULL)
			return (0);
		else
			ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	return (0);
}

int	ft_cd(t_minishell *minishell, t_token_list *command)
{
	char		*dir;
	struct stat	st;

	if (too_many_args(command))
		return (1);
	if (should_go_home(command) == 1)
		return (get_home(minishell));
	dir = command->next->name;
	if (ft_strncmp(dir, ".", 1) && stat(dir, &st) == -1)
	{
		print_cmd_perror("cd", dir, errno);
		return (1);
	}
	if (contains_only_charset(dir, "./"))
		return (go_into_directory(minishell, ft_realpath(minishell, dir)));
	if (ft_strncmp(dir, ".", 1) && !(S_ISDIR(st.st_mode)))
		// if doesn't begin with . and is not dir
		print_cmd_perror("cd", dir, ENOTDIR);
	else
		return (go_into_directory(minishell, dir));
	return (0);
}
// dprintf(2, "bash: cd: %s: Not a directory\n", dir);
// if (access(dir, F_OK | X_OK))
// {
// 	perror("access");
// }
/*
http://pwet.fr/man/linux/commandes/posix/cd/
cd ../../../
char		*getcwd(char *buf, size_t size);
La fonction getcwd() copie le chemin d'accès absolu du répertoire de travail courant dans la chaîne pointée par buf,
	qui est de longueur size.
Si le chemin du répertoire en cours nécessite un tampon plus long que size octets,
	la fonction renvoie NULL,
	et errno contient le code d'erreur ERANGE. Une application doit détecter cette erreur et allouer un tampon plus grand si besoin est.
Si buf est NULL, le comportement de getcwd() est indéfini.
Dans quels cas getcwd peut echouer ?

`getcwd()` est une fonction de la bibliothèque standard C qui renvoie le chemin absolu du répertoire courant. Cette fonction peut échouer dans les cas suivants :

1. Le tampon fourni n'est pas assez grand pour contenir le chemin complet du répertoire courant. Dans ce cas,
	`getcwd()` renvoie `NULL` et définit `errno` à `ERANGE`.
2. Le répertoire courant a été supprimé ou déplacé. Dans ce cas,
	`getcwd()` renvoie `NULL` et définit `errno` à `ENOENT`.
mbernard@z4r9p5:~/test/test/test$ cd ..
cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
3. Le processus n'a pas les permissions nécessaires pour accéder au répertoire courant ou à l'un de ses parents. Dans ce cas,
	`getcwd()` renvoie `NULL` et définit `errno` à `EACCES` ou `EPERM`.
mbernard@z4r9p5:~/test/test$ cd ..
bash: cd: ..: Permission denied
4. Le système de fichiers est en mode lecture seule ou le processus a atteint sa limite de ressources. Dans ce cas,
	`getcwd()` renvoie `NULL` et définit `errno` à `EIO` ou `ENOMEM`.
5. Le chemin du répertoire courant contient des liens symboliques circulaires. Dans ce cas,
	`getcwd()` peut renvoyer `NULL` et définir `errno` à `ELOOP`.
mbernard@z4r9p5:~/test/test/test$ cd ..
cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory

int			chdir(const char *path);
chdir() remplace le répertoire de travail courant du processus appelant par celui indiqué dans le chemin path.
https://www.thegeekstuff.com/2010/10/linux-error-codes/
int			access(const char *pathname, int mode);
access() vérifie si le processus appelant peut accéder au fichier pathname. Si pathname est un lien symbolique,
	il est déréférencé.

Le mode indique la (les) vérification(s) d'accessibilité à effectuer et est soit la valeur F_OK,
	soit un masque constitué par un OU binaire « | » entre les valeurs R_OK,
	W_OK et X_OK. F_OK R_OK, W_OK et X_OK servent à tester respectivement,
	si le fichier existe, la lecture, l'écriture et l'exécution du fichier.

Le test est effectué avec les UID et GID réels du processus appelant,
	plutôt qu'avec les IDs effectifs qui sont utilisés lorsque l'on tente une opération (par exemple,
	open(2)) sur le fichier. Ceci permet aux programmes Set-UID de déterminer les autorisations de l'utilisateur ayant invoqué le programme.

Si le processus appelant est privilégié (c'est-à-dire, son UID réel est nul),
	une vérification X_OK sur un fichier régulier réussit même si le fichier n'a aucun bit d'exécution positionné.

d-w------- 2 mbernard 2023_lyon   6 Apr 10 11:04 dossier
dr--r--r-- 2 mbernard 2023_lyon   6 Apr 10 11:04 dossier
bash: cd: dossier/: Permission denied
d--x--x--x 2 mbernard 2023_lyon   6 Apr 10 11:04 dossier
--> fonctionne uniquement si permission d'execution :
mbernard@z4r9p5:~$ chmod 777 dossier
mbernard@z4r9p5:~$ chmod -x dossier
mbernard@z4r9p5:~$ cd dossier/
bash: cd: dossier/: Permission denied
drw-rw-rw- 2 mbernard 2023_lyon   6 Apr 10 11:04 dossier
bernard@z4r9p5:~$ cd fichier
bash: cd: fichier: Not a directory
Bash verifie que c'est un repertoire avant de verifier les droits :
mbernard@z4r9p5:~$ touch fichier
mbernard@z4r9p5:~$ chmod 000 fichier
mbernard@z4r9p5:~$ cd fichier
bash: cd: fichier: Not a directory
mbernard@z4r9p5:/home/mbernard$ cd
bash: cd: HOME not set
mbernard@z4r9p5:/home/mbernard$ echo $?
1

*/
