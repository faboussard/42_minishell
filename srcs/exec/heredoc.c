/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:20:54 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/11 10:41:39 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"

void check_and_delete_if_tmp_file_exists(char *tmp_file)
{
	if (access(tmp_file, F_OK) == 0)
	{
		if (unlink(tmp_file) == -1)
			perror("");
	}
}

void handle_expand(t_minishell *m, char *input)
{
	char **split_space;
	char **split_dollar;
	char *input_after_expand;
	char *temp;
	int i = 0; // Initialise i à zéro
	int j;
	int count = -1;

	split_space = ft_split(input, ' ');
	if (split_space == NULL)
		exit_msg_minishell(m, "Fatal : malloc failed at handle expand", -1);
	input_after_expand = ft_calloc(1, 1);
	input_after_expand[0] = '\0';
	while (split_space[i])
	{
		if (ft_strchr(split_space[i], '$') != NULL)
		{
			j = 0;
			temp = ft_calloc(ft_strlen(split_space[i]) + 1, sizeof(char)); // Alloue temp correctement
			while (split_space[i][j] && split_space[i][j] != '$')
			{
				temp[j] = split_space[i][j];
				j++;
			}
			if (j != 0)
			{
				input_after_expand = ft_strjoin(input_after_expand, temp);
				ft_memmove(split_space[i], split_space[i] + j, ft_strlen(split_space[i] + j) + 1);
			}
			free(temp);
			temp = NULL;// Libère temp après utilisation
			// on cherche les envp
			j = 0; // Réinitialise j
			split_dollar = ft_split(split_space[i], '$');
			while (split_dollar[j])
			{
				temp = expand_sigil(split_dollar[j], m);
				if (temp != split_dollar[j])
				{
					count ++;
					if (count == i && count != 0)
						input_after_expand = ft_strjoin(input_after_expand, " ");
					input_after_expand = ft_strjoin(input_after_expand, temp);
				}
				free(split_dollar[j]);
				temp = NULL;// Libère la mémoire allouée pour split_dollar[j]
				j++;
			}
			free(split_dollar); // Libère la mémoire allouée pour split_dollar
		}
		else
			input_after_expand = ft_strjoin(input_after_expand, split_space[i]);
		free(split_space[i]); // Libère la mémoire allouée pour split_space[i]
		i++; // Incrémente i à chaque itération
	}
	free(split_space);
	printf("ouput : %s\n",input_after_expand);
//	if (input_after_expand != NULL)
//		ft_putstr_fd(input_after_expand, m->fd_in);
//	else
//		ft_putstr_fd(input, m->fd_in);
//	if (input_after_expand != NULL)
//		free(input_after_expand);
}

static void writing_in_heredoc(t_minishell *m, char *limiter)
{
	size_t limiter_len;
	size_t input_len;
	char *input;

	limiter_len = ft_strlen(limiter);
//	while (1)
//	{
	input = get_next_line(STDIN_FILENO);
	input_len = ft_strlen(input) - 1;
	if (input_len == limiter_len && !ft_strncmp(input, limiter,
												limiter_len))
	{
		free(input);
		close(m->fd_in);
		exit(0);
	}
	handle_expand(m, input);
	free(input);
//	}
}

void here_doc(t_minishell *m, char *limiter)
{
	check_and_delete_if_tmp_file_exists(HERE_DOC_TMP_FILE);
	m->fd_in = open(HERE_DOC_TMP_FILE, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (m->fd_in < 0)
	{
		perror("No /tmp/ directory found");
		return;
	}
	// A CHANGER, pas d'exit du minishell
//	m->pid1 = m_safe_fork(m);
//	if (m->pid1 == 0)
	writing_in_heredoc(m, limiter);
//	else
//	{
	while (waitpid(-1, &(m->status), 0) && errno != 10);
	close(m->fd_in);
//	}
}
