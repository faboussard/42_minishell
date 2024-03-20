
#include "../../inc/libft.h"

/// @brief 			Returns the index of the t_list where target could be found
///						if it is in the hashmap_dictionnary
/// @param target 	String from which the index is generated
/// @return 		Returns the index of the t_list where target could be found
///						if it is in the hashmap_dictionnary
size_t	ft_hm_get_index(char *target)
{
	size_t	target_value;
	size_t	multiplier;
	size_t	i;

	target_value = 0;
	multiplier = 1;
	i = 0;
	while (target[i] != '\0')
	{
		target_value += target[i] * multiplier;
		multiplier *= 10;
		i++;
	}
	return (target_value % HASHMAP_ARR_SIZE);
}
