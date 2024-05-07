/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:18:22 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/06 14:38:22 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	manage_fd_error(t_minishell *m, t_process_list *pl, int *fd_to_use)
{
	if (pl->in_files_token->e_type == DELIMITER)
		perror("minishell: heredoc file can't be opened");
	else
		print_name(m, pl->in_files_token->name);
	m->status = 1;
	pl->dev_null = 1;
	*fd_to_use = open("/dev/null", O_RDONLY);
	if (*fd_to_use < 0)
		ft_putendl_fd("Couldn't open /dev/null/", 2);
}

int	open_fd_infile(t_minishell *m, t_process_list *pl, int *fd_to_use)
{
	enum e_token_type	infile_type;

	infile_type = pl->in_files_token->e_type;
	pl->dev_null = 0;
	if (infile_type == DELIMITER || infile_type == IN_FILE)
		close_fds(*fd_to_use, 0);
	if (infile_type == DELIMITER)
		*fd_to_use = open(HERE_DOC_TMP_FILE, O_RDONLY);
	else if (infile_type == IN_FILE)
		*fd_to_use = open(pl->in_files_token->name, O_RDONLY);
	else
		pl->fd_in = STDIN_FILENO;
	if (*fd_to_use < 0)
	{
		manage_fd_error(m, pl, fd_to_use);
		return (1);
	}
	return (0);
}

int	open_fd_outfile(t_minishell *m, t_process_list *pl, char *out)
{
	if (pl->out_files_token->e_type == OUT_FILE)
		pl->fd_out = open(out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (pl->out_files_token->e_type == APPEND_FILE)
		pl->fd_out = open(out, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		pl->fd_out = STDOUT_FILENO;
	if (pl->fd_out < 0)
	{
		print_name_and_give_status(m, out, 1);
		return (1);
	}
	return (0);
}

void	handle_in_out(t_minishell *m, t_process_list *pl, int *fd_in)
{
	enum e_token_type	infile_token;

	infile_token = pl->in_files_token->e_type;
	if (infile_token == DELIMITER)
		here_doc(m, pl->in_files_token, fd_in, pl);
	if (open_fd_infile(m, pl, fd_in))
		return ;
	open_fd_outfile(m, pl, pl->out_files_token->name);
}

void	close_and_redirect_pipe_to_stdin(t_minishell *m, t_process_list *pl)
{
	if (m->pipe_fd[WRITE_END] > 0)
		close(m->pipe_fd[WRITE_END]);
	if (pl->fd_in >= 3)
		close(pl->fd_in);
	if (m->tmp_in >= 3)
		close(m->tmp_in);
	m->tmp_in = m->pipe_fd[READ_END];
	if (pl->fd_out != STDOUT_FILENO)
		close(pl->fd_out);
}

/*
Pour rediriger l'extrémité du tube vers `/dev/null` lorsque vous avez un fichier
 d'entrée dans le pipe suivant, vous pouvez utiliser la fonction `dup2()`. Cette
 fonction fait en sorte qu'un descripteur de fichier pointe vers le même fichier
 qu'un autre descripteur de fichier.

Dans votre cas, vous pouvez ouvrir `/dev/null` et utiliser `dup2()` pour faire
 en sorte que l'extrémité de sortie du tube pointe vers `/dev/null`. Cela
 signifie que tout ce qui est écrit dans le tube sera envoyé à `/dev/null`, ce
 qui est équivalent à être supprimé.

Voici un exemple de comment vous pourriez le faire dans votre code :

```c
int dev_null_fd = open("/dev/null", O_WRONLY);
if (dev_null_fd < 0) {
    perror("Couldn't open /dev/null");
    return;
}

// Duplique dev_null_fd vers l'extrémité de sortie du tube
if (dup2(dev_null_fd, m->pipe_fd[WRITE_END]) < 0) {
    perror("dup2 failed");
    return;
}

// Ferme le descripteur de fichier original pour /dev/null
close(dev_null_fd);
```

Cela devrait être fait après avoir créé le tube, mais avant d'écrire dans le
tube.
Notez que vous devrez également gérer les erreurs pour `open()` et `dup2()`.

 int dev_null_fd;

dev_null_fd = open("/dev/null", O_TRUNC);
if (dev_null_fd < 0) {
perror("Couldn't open /dev/null");
return (1);
}
 if (infile_type == DELIMITER || infile_type == IN_FILE)
 {
		if (m->total_commands > 1)
		m_safe_dup2(m, dev_null_fd, m->pipe_fd[WRITE_END]);
 	close_fds(*fd_to_use, 0);
}
 */
