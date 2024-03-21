
#include "../../inc/libft.h"

t_hashmap	ft_hm_init(void)
{
	return (ft_calloc(HASHMAP_ARR_SIZE, sizeof(t_hashmap)));
}
