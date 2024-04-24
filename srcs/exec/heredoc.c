/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:20:54 by mbernard          #+#    #+#             */
/*   Updated: 2024/04/23 08:55:57 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"

void	handle_expand(t_minishell *m, char *input)
{
	char	**split_space;
	char	*input_after_expand;

	split_space = ft_split(input, ' ');
	if (split_space == NULL)
		exit_msg_minishell(m, "Fatal : malloc failed at handle expand", -1);
	input_after_expand = expand_variables(m, split_space);
	if (input_after_expand != NULL)
		ft_putstr_fd(input_after_expand, m->fd_in);
	else
		ft_putstr_fd(input, m->fd_in);
	if (input_after_expand != NULL)
		free(input_after_expand);
	if (split_space != NULL)
		ft_free_tab(split_space);
}

char	*expand_variables(t_minishell *m, char **split_space)
{
	char	*input_after_expand;
	int		count;
	int		i;

	input_after_expand = ft_calloc(1, 1);
	input_after_expand[0] = '\0';
	count = -1;
	i = 0;
	while (split_space[i])
	{
		if (is_quoted_variable(split_space[i]))
			handle_quoted_variable(m, &input_after_expand, split_space[i]);
		else
			handle_regular_variable(m, &input_after_expand, split_space[i],
				&count, &i);
		i++;
	}
	return (input_after_expand);
}

void	handle_quoted_variable(t_minishell *m, char **input_after_expand,
		char *variable)
{
	char	*expanded;
//	char	*temp;

	expanded = expand_sigil(variable, m);
	if (expanded != variable)
	{
	//	temp = ft_calloc(1, 1);
		*input_after_expand = ft_strjoin(*input_after_expand, expanded);
	}
}

void	handle_regular_variable(t_minishell *m, char **input_after_expand,
		char *variable, int *count, int *i)
{
	char	*temp;
	char	**split_dollar;
	int		j;

	j = 0;
	temp = get_non_variable_part(m, variable);
	if (temp != NULL)
	{
		(*count)++;
		if (*count != 0 && *count >= *i)
			*input_after_expand = ft_strjoin(*input_after_expand, " ");
		*input_after_expand = ft_strjoin(*input_after_expand, temp);
		free(temp);
	}
	split_dollar = ft_split(variable, '$');
	if (split_dollar == NULL)
		exit_msg_minishell(m, "Malloc failed at handle expand", -1);
	while (split_dollar[j])
	{
		handle_quoted_variable(m, input_after_expand, split_dollar[j]);
		j++;
	}
	ft_free_tab(split_dollar);
}

char	*get_non_variable_part(t_minishell *m, char *string)
{
	int		i;
	char	*temp;

	i = 0;
	while (string[i] && string[i] != '$')
		i++;
	if (i != 0)
	{
		temp = ft_substr(string, 0, i);
		if (temp == NULL)
			exit_msg_minishell(m, "Malloc failed at handle expand", -1);
		return (temp);
	}
	return (NULL);
}

int	is_quoted_variable(char *string)
{
	if (string[0] == '$' && (string[1] == '\'' || string[1] == '\"'))
		return (1);
	return (0);
}

static void	writing_in_heredoc(t_minishell *m, char *limiter, int stdin_fd)
{
	size_t	limiter_len;
	size_t	input_len;
	char	*input;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		input = get_next_line(stdin_fd);
		input_len = ft_strlen(input) - 1;
		if (input_len == limiter_len && !ft_strncmp(input, limiter,
				limiter_len))
		{
			free(input);
			close(m->fd_in);
			exit(0);
		}
		handle_expand(m, input);
		// ajouter a la reqalif si le delimiteur est un quoted heredoc ou un non quotes heredoc
		// cela changera sa gestion a lexpansion du heredoc
		free(input);
	}
}

void	here_doc(t_minishell *m, char *limiter, int stdin_fd, int fd_to_use)
{
    int here_doc_pid;

    close_fds(fd_to_use, -1);
    fd_to_use = open(HERE_DOC_TMP_FILE, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd_to_use < 0)
	{
		perror("No /tmp/ directory found");
		return ;
	}
	// A CHANGER, pas d'exit du minishell
    here_doc_pid = m_safe_fork(m);
	if (here_doc_pid == 0)
		writing_in_heredoc(m, limiter, stdin_fd);
	else
	{
		waitpid(here_doc_pid, &(m->status), 0); // && errno != 10);
		close(fd_to_use);
	}
}
/*
 * Impossible de remplacer m->fd_in par un fd_here_doc local, fait foirer
 * la suite : un << compte wc -l donnera toujours 0 au lieu de compter
 * si on n'utilise pas fd_in
 */