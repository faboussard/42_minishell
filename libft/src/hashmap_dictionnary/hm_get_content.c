
#include "../../inc/libft.h"

/// @brief 			Returns hashmap_dictionnary value at target,
///						returns NULL if it doesn't exist
/// @param map 		Hashmap in which to search for target
/// @param target 	Where the value is stored in hashmap_dictionnary
/// @return 		Returns hashmap_dictionnary value at target,
///						returns NULL if it doesn't exist
void	*ft_hm_get_content(t_hashmap map, char *target)
{
	t_hashmap_content	*elem;

	elem = ft_hm_get_elem(map, target);
	if (elem == NULL)
		return (NULL);
	return (elem->content);
}
