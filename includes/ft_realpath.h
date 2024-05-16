/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 08:29:45 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/16 08:39:08 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REALPATH_H
#define FT_REALPATH_H
#include "builtins.h"
#include "exec.h"

typedef struct s_nodes_list
{
	char	*subdir;
	struct s_nodes_list	*next;
	struct s_nodes_list	*prev;
}						t_nodes_list;

void	ft_free_list(t_nodes_list *list);
t_nodes_list 	*ft_split_list(char const *s, char c);

#endif //FT_REALPATH_H
