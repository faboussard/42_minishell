
#include "../../inc/libft.h"

/// @brief 			returns the t_hashmap_content* (a) in the hashmap that has
///						a->target == target, returns NULL if it doesn't exist
/// @param map 		Hashmap in which to search for target
/// @param target 	string to look for in the hashmap
/// @return 		returns the t_hashmap_content* (a) in the hashmap that has
///						a->target == target, returns NULL if it doesn't exist
t_hashmap_content	*ft_hm_get_elem(t_hashmap map, char *target)
{
	t_node	*cursor;

	if (target == NULL)
		return (NULL);
	cursor = map[ft_hm_get_index(target)];
	while (cursor != NULL
		&& ft_strcmp(((t_hashmap_content *)cursor->content)->target, target)
		!= 0)
		cursor = cursor->next;
	if (cursor == NULL)
		return (NULL);
	return (cursor->content);
}
