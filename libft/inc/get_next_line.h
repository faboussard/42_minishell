/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:42:31 by faboussa          #+#    #+#             */
/*   Updated: 2024/01/10 09:22:00 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"

# define LINE_MAX_SIZE 50000

# define SET_INDEX 1
# define FIND_INDEX 2
# define EMPTY 3

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif //BUFFER_SIZE

char	*get_next_line(int fd);
char	*ft_concat(char *dst, const char *src, size_t src_len, size_t dstsize);
int		ft_strchri(const char *s, size_t len, char c, size_t index);
char	*cook_line(char *s);
int		ft_stash(const int action, char (*stash)[BUFFER_SIZE],
			size_t current_index);
char	*init_line(int fd, ssize_t *n_read);

#endif // GET_NEXT_LINE_H