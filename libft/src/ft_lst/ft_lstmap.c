/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:48:20 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/22 12:11:26 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

t_node	*ft_lstmap(t_node *lst, void *(*f)(void *), void (*del)(void *))
{
	t_node	*new_list;
	t_node	*new_node;
	void	*content_node;

	new_list = NULL;
	if (f == NULL || del == NULL)
		return (NULL);
	while (lst != NULL)
	{
		content_node = f(lst->content);
		if (content_node == NULL)
			return (NULL);
		new_node = ft_lstnew(content_node);
		if (new_node == NULL)
		{
			ft_lstclear(&new_node, del);
			del(content_node);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
