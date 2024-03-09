/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:47:09 by faboussa          #+#    #+#             */
/*   Updated: 2024/01/10 10:39:43 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*cook_line(char *s)
{
	int		size;
	char	*s2;
	int		i;

	i = 0;
	size = ft_strlen(s);
	s2 = malloc(size + 1);
	if (s2 == NULL)
		return (free(s), NULL);
	while (i < size)
	{
		s2[i] = s[i];
		i++;
	}
	s2[size] = '\0';
	free(s);
	return (s2);
}

int	ft_stash(const int action, char (*stash)[BUFFER_SIZE], size_t current_index)
{
	size_t	i;
	size_t	is_buffer_size;

	is_buffer_size = BUFFER_SIZE;
	i = 0;
	if (action == SET_INDEX)
	{
		while (i < current_index)
			(*stash)[i++] = '\0';
	}
	else if (action == FIND_INDEX)
	{
		while ((*stash)[i] == '\0')
			i++;
		return (i % is_buffer_size);
	}
	else if (action == EMPTY)
	{
		while (i < is_buffer_size)
			if ((*stash)[i++] != '\0')
				return (0);
		return (1);
	}
	return (-1);
}

char	*fill_line(char *line, char (*stash)[BUFFER_SIZE], int *i, int pos)
{
	char	*substring;

	*i = ft_stash(FIND_INDEX, stash, 0);
	if (pos == -1)
	{
		line = ft_concat(line, *stash + *i, BUFFER_SIZE - *i,
				LINE_MAX_SIZE);
		if (!line)
			return (free(line), ft_stash(SET_INDEX, stash, BUFFER_SIZE), NULL);
		ft_stash(SET_INDEX, stash, BUFFER_SIZE);
		*i = 0;
	}
	else
	{
		substring = ft_substr_gnl(*stash, BUFFER_SIZE, *i, pos - *i + 1);
		if (!substring)
			return (free(line), ft_stash(SET_INDEX, stash, BUFFER_SIZE), NULL);
		line = ft_concat(line, substring, ft_strlen(substring), LINE_MAX_SIZE);
		if (!line)
			return (ft_stash(SET_INDEX, stash, BUFFER_SIZE), free(substring),
				NULL);
		ft_stash(SET_INDEX, stash, pos + 1);
		free(substring);
	}
	return (line);
}

char	*init_line(int fd, ssize_t *n_read)
{
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		exit(EXIT_FAILURE);
	*n_read = 1;
	line = malloc(sizeof(char) * LINE_MAX_SIZE);
	if (line == NULL)
		exit(EXIT_FAILURE);
	line[0] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE];
	int			current_index;
	int			pos;
	char		*line;
	ssize_t		n_read;

	line = init_line(fd, &n_read);
	while (!ft_stash(EMPTY, &stash, 0) || read(fd, stash, BUFFER_SIZE) > 0)
	{
		current_index = ft_stash(FIND_INDEX, &stash, 0);
		pos = ft_strchri(stash, BUFFER_SIZE, '\n', current_index);
		line = fill_line(line, &stash, &current_index, pos);
		if (line == NULL)
			return (ft_stash(SET_INDEX, &stash, BUFFER_SIZE), NULL);
		if (pos != -1)
			break ;
		n_read = read(fd, stash, BUFFER_SIZE);
	}
	if (line[0] == '\0' || n_read < 0)
		return (ft_stash(SET_INDEX, &stash, BUFFER_SIZE), free(line), NULL);
	return (cook_line(line));
}
