
#include "../../inc/libft.h"
#include <stdlib.h>

static void	free_hashmap_list(t_node *lst, void (*del)(void *));

/// @brief 		Frees all elements of a hashmap and sets it to NULL
/// @param map 	Hashmap to free
/// @param del 	Fonction to free hashmap content
void	ft_hm_clear(t_hashmap *map, void (*del)(void *))
{
	size_t	i;

	if (map == NULL || *map == NULL)
		return ;
	i = 0;
	while (i < HASHMAP_ARR_SIZE)
	{
		free_hashmap_list((*map)[i], del);
		i++;
	}
	free(*map);
	*map = NULL;
}

static void	free_hashmap_list(t_node *lst, void (*del)(void *))
{
	t_hashmap_node	*node_content;

	if (lst == NULL)
		return ;
	free_hashmap_list(lst->next, del);
	node_content = lst->content;
	if (lst->content != NULL)
	{
		if (del != NULL && node_content->content != NULL)
			del(node_content->content);
		free(node_content->target);
	}
	free(lst->content);
	free(lst);
}
