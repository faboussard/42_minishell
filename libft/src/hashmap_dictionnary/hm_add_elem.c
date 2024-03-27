
#include "../../inc/libft.h"
#include <stdlib.h>
#include "../../includes/lexer.h"

#define NOT_FOUND 1
#define MALLOC_FAILED -1
#define SUCCESSFULLY_ADDED 0

static int	modify_if_exists(t_node *dst, char *target, void *content,
				void (*del)(void *));
static int	add_new(t_node **dst, char *target, void *content);

/// @brief 			Used to add an elem to the hashmap_dictionnary
/// @param map 		Hashmap in which to insert the elem
/// @param target 	Used to find the elem in the hashmap_dictionnary
///						(doesn't need to be malloced)
/// @param content 	Content to add to the hashmap_dictionnary
///						(needs to be malloced)
/// @param del 		Fonction to delete value that might already be at target
///						(pass NULL if you don't want to free previous value)
/// @return			0 if successful, -1 if malloc failed
int	ft_hm_add_elem(t_hashmap map, char *target, void *content,
			void (*del)(void *))
{
	size_t	index;

	index = ft_hm_get_index(target);
	if (modify_if_exists(map[index], target, content, del)
		== SUCCESSFULLY_ADDED)
		return (SUCCESSFULLY_ADDED);
	return (add_new(map + index, target, content));
}

static int	modify_if_exists(t_node *dst, char *target, void *content,
				void (*del)(void *))
{
	while (dst != NULL
		&& ft_strcmp(((t_envp_content *)dst->content)->target, target) != 0)
		dst = dst->next;
	if (dst == NULL)
		return (NOT_FOUND);
	if (del == NULL)
	{
		((t_envp_content *)dst->content)->value = content;
		((t_envp_content *)dst->content)->value_size = ft_strlen(content);
		return (SUCCESSFULLY_ADDED);
	}
	del(((t_envp_content *)dst->content)->value);
	((t_envp_content *)dst->content)->value = content;
	((t_envp_content *)dst->content)->value_size = ft_strlen(content);
	return (SUCCESSFULLY_ADDED);
}

static int	add_new(t_node **dst, char *target, void *content)
{
	t_envp_content	*new_node_content;
	t_node				*new_node;

	new_node_content = malloc(sizeof(t_envp_content));
	if (new_node_content == NULL)
		return (MALLOC_FAILED);
	new_node_content->value = content;
	new_node_content->target = ft_strdup(target);
	new_node_content->value_size = ft_strlen(new_node_content->value);
	new_node_content->target_size = ft_strlen(new_node_content->target);
	if (new_node_content->target == NULL)
	{
		free(new_node_content);
		return (MALLOC_FAILED);
	}
	new_node = ft_lstnew(new_node_content);
	if (new_node == NULL)
	{
		free(new_node_content->target);
		free(new_node_content);
		return (MALLOC_FAILED);
	}
	ft_lstadd_front(dst, new_node);
	return (SUCCESSFULLY_ADDED);
}