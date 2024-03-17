
#include "../../inc/libft.h"
#include <stdlib.h>

# define LAST_EXIT_CODE "?"

void	print_hashmap(t_hashmap env_variables)
{
	int					i;
	t_node				*cursor;
	t_hashmap_content	*hm_content;

	cursor = NULL;
	hm_content = NULL;
	ft_printf("--------------- Hashmap ---------------\n");
	i = HASHMAP_ARR_SIZE;
	while (i-- > 0)
	{
		cursor = env_variables[i];
		while (cursor != NULL)
		{
			hm_content = cursor->content;
			if (hm_content != NULL && hm_content->target != NULL)
				ft_printf("%s=%s\n", hm_content->target, (char *)hm_content->content);
			cursor = cursor->next;
		}
	}
}