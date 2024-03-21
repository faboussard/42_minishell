
#include "../../inc/libft.h"

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
