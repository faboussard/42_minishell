/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/09 22:02:34 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_lstsize_envp(t_envp_list *lst)
{
	int	i;
	int	list_size;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	list_size = i;
	return (list_size);
}

char	*trim_equal_sign(char *key)
{
	char	*trimmed_key;

	trimmed_key = ft_strtrim(key, "=");
	if (trimmed_key == NULL)
		return (NULL);
	return (trimmed_key);
}

void	remove_node_envp(t_envp_list **begin_list, t_envp_list *node_to_remove)
{
	t_envp_list	*current;
	t_envp_list	*previous_node;

	current = *begin_list;
	previous_node = NULL;
	while (current != NULL && current != node_to_remove)
	{
		previous_node = current;
		current = current->next;
	}
	if (current == node_to_remove)
	{
		if (previous_node != NULL)
			previous_node->next = current->next;
		else
			*begin_list = current->next;
		free_envp(current);
	}
}
