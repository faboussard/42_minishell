
#include "../../inc/libft.h"
#include "../../includes/lexer.h"
#include <stdlib.h>

static void	free_hashmap_list(t_node *lst, void (*del)(void *));

/// @brief 		Frees all elements of a hashmap_dictionnary and sets it to NULL
/// @param map 	Hashmap to free
/// @param del 	Fonction to free hashmap_dictionnary value
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
	t_envp_content	*node_content;

	if (lst == NULL)
		return ;
	free_hashmap_list(lst->next, del);
	node_content = lst->content;
	if (lst->content != NULL)
	{
		if (del != NULL && node_content->value != NULL)
			del((void *)node_content->value);
		free(node_content->target);
	}
	free(lst->content);
	free(lst);
}
