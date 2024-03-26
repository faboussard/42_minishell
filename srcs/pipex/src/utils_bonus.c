/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:15:47 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/25 14:12:04 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab || !*tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	ft_init_struct(t_pipex *pipex)
{
	pipex->status = 0;
	pipex->here_doc = 0;
	pipex->dev_null = 0;
	pipex->tmp_in = 0;
	pipex->fd_in = -1;
	pipex->fd_out = -1;
	pipex->paths = NULL;
	pipex->good_path = NULL;
	pipex->tab_paths = NULL;
	pipex->cmd_args = NULL;
	pipex->cmd = NULL;
}

void	ft_free_struct(t_pipex *pipex)
{
	if (pipex->fd_in >= 0)
		close(pipex->fd_in);
	if (pipex->fd_out >= 0)
		close(pipex->fd_out);
	if (pipex->tmp_in >= 0)
		close(pipex->tmp_in);
	if (pipex->paths)
		free(pipex->paths);
	if (pipex->good_path)
		free(pipex->good_path);
	if (pipex->tab_paths)
		ft_free_tab(pipex->tab_paths);
	if (pipex->cmd_args)
		ft_free_tab(pipex->cmd_args);
	if (pipex->cmd)
		free(pipex->cmd);
	if (pipex->here_doc == 1)
		check_and_delete_if_tmp_file_exists("/tmp/.tmp_heredoc");
	close(STDOUT_FILENO);
}

void	check_and_delete_if_tmp_file_exists(char *tmp_file)
{
	if (access(tmp_file, F_OK) == 0)
	{
		if (unlink(tmp_file) == -1)
			perror("");
	}
}

void	erase_spaces_in_cmd_args(t_pipex *p)
{
	int	x;

	x = 0;
	while (p->cmd_args[0][x])
	{
		if (p->cmd_args[0][x] == ' ')
			p->cmd_args[0][x] = '\0';
		x++;
	}
}
