
#include "../../inc/libft.h"

/// @brief 			Returns hashmap content at target,
///						returns NULL if it doesn't exist
/// @param map 		Hashmap in which to search for target
/// @param target 	Where the content is stored in hashmap
/// @return 		Returns hashmap content at target,
///						returns NULL if it doesn't exist
void	*ft_hm_get_content(t_hashmap map, char *target)
{
	t_hashmap_node	*elem;

	elem = ft_hm_get_elem(map, target);
	if (elem == NULL)
		return (NULL);
	return (elem->content);
}
