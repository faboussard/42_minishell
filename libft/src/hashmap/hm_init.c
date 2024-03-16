
#include "../../inc/libft.h"

/// @brief 		Mallocs a hashmap and sets all its t_list to NULL
/// @return 	Returns an empty hashmap
t_hashmap	ft_hm_init(void)
{
	return (ft_calloc(HASHMAP_ARR_SIZE, sizeof(t_hashmap)));
}
