
#include "../../inc/libft.h"

/// @brief 			Returns the number of elements in hashmap_dictionnary
/// @param hashmap 	Hashmap in which the number of elem is counted
/// @return 		Returns the number of elements in hashmap_dictionnary
int	ft_hm_size(t_hashmap hashmap)
{
	int		size;
	int		i;
	t_node 	*cursor;

	if (hashmap == NULL)
		return (0);
	size = 0;
	i = HASHMAP_ARR_SIZE;
	while (i-- > 0)
	{
		cursor = hashmap[i];
		while (cursor != NULL)
		{
			size++;
			cursor = cursor->next;
		}
	}
	return (size);
}
