/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:25:35 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/31 20:41:21 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signal.h"
#include "signals.h"

void	delete_here_doc_files(t_process_list *pl)
{
	t_process_list	*tmp;

	tmp = pl;
	while (tmp != NULL)
	{
		check_and_delete_if_tmp_file_exists(tmp);
		tmp = tmp->next;
	}
}

void	fill_heredoc_file_name(t_minishell *m, t_process_list **pl)
{
	int		num;
	char	*str_num;
	char	*str_joined;

	if ((*pl)->here_doc_file[0] != 0)
		check_and_delete_if_tmp_file_exists(*pl);
	num = INT_MIN;
	while ((*pl)->here_doc_file[0] == 0
		|| access((*pl)->here_doc_file, F_OK) == 0)
	{
		str_num = ft_itoa(num);
		if (str_num == NULL)
			exit_msg(m, "Malloc failed at heredoc", ENOMEM);
		str_joined = ft_strjoin("/tmp/.tmp_heredoc", str_num);
		free_safely_str(&str_num);
		if (str_joined == NULL)
			exit_msg(m, "Malloc failed at heredoc", ENOMEM);
		ft_strlcpy((*pl)->here_doc_file, str_joined, 28);
		free_safely_str(&(str_joined));
		num++;
		if (num == INT_MIN)
			exit_msg(m, "Heredoc error : couldn't create the tmp file", 1);
	}
}

void	perror_exit_heredoc(t_minishell *m, t_process_list *pl, char **input)
{
	free_safely_str(&(*input));
	perror("Can't write in heredoc file");
	close_all_fds(m, pl);
	free_minishell(m);
	exit(errno);
}
