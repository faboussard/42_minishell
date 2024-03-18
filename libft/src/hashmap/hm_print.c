
#include "../../inc/libft.h"
#include <stdlib.h>

void	print_hashmap(t_hashmap env_variables)
{
	int					i;
	t_node				*cursor;
	t_hashmap_content	*hm_content;

	ft_printf("--------------- Hashmap ---------------\n");
	i = HASHMAP_ARR_SIZE;
	int size = ft_hm_size(env_variables);
	ft_printf("Size: %d\n", size);
	while (i-- > 0)
	{
		cursor = env_variables[i];
		while (cursor != NULL)
		{
			hm_content = cursor->content;
			if (hm_content != NULL)
				ft_printf("%s=%s\n", hm_content->target, (char *)hm_content->content);
			cursor = cursor->next;
		}
	}
}