/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 08:29:45 by mbernard          #+#    #+#             */
/*   Updated: 2024/05/18 22:38:16 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REALPATH_H
# define FT_REALPATH_H
# include "builtins.h"
# include "exec.h"

typedef struct s_dir_list
{
	char				*subdir;
	struct s_dir_list	*next;
	struct s_dir_list	*prev;
}						t_dir_list;

////////////////////////////    SPLIT LIST        //////////////////////////////
t_dir_list				*ft_split_list(char const *s, char c);
void					ft_free_list(t_dir_list *list);
////////////////////////////    REALPATH UTILS    //////////////////////////////
void					remove_node_from_list(t_dir_list *node);
size_t					count_up_moves(char *cmd);
size_t					count_moves_to_root(char *cmd);
bool					invalid_num_of_pts(char *dir);
char					*join_sep_safely(char *s1, char *s2, char sep,
							bool free_s1);

#endif // FT_REALPATH_H
