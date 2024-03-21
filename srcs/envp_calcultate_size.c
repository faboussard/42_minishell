/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_table.c		                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>


//void create_target_tab(t_hashmap_struct *hashmap)
//{
//	hashmap->target_tab = (char **)ft_calloc(total_size + 1, sizeof(char *));
//	if (hashmap->target_tab == NULL)
//		return 0;
//	index = 0;
//	size_t target_index = 0;
//	while (index < HASHMAP_ARR_SIZE)
//	{
//		t_node *cursor = dict_chain[index];
//		while (cursor != NULL)
//		{
//			hashmap->target_tab[target_index] = ft_strdup(((t_hashmap_content *)cursor->content)->target);
//			if (hashmap->target_tab[target_index] == NULL)
//				return 0;
//			target_index++;
//			cursor = cursor->next;
//		}
//		index++;
//	}
//}

size_t calculate_total_target_size(t_hashmap_struct *hashmap)
{
	size_t target_size = 0;
	size_t index = 0;
	t_dict dict_chain = hashmap->dict_chain;

	while (index < HASHMAP_ARR_SIZE)
	{
		t_node *cursor = dict_chain[index];
		while (cursor != NULL)
		{
			target_size += ((t_dict_content *) cursor->content)->target_size;
			cursor = cursor->next;
		}
		index++;
	}
	return (target_size);
}


size_t calculate_total_value_size(t_dict envp_dict)
{
	size_t					i;
	t_node				*cursor;
	size_t				value_size;

	i = 0;
	value_size = 0;
	while (i < HASHMAP_ARR_SIZE)
	{
		cursor = envp_dict[i];
		while (cursor != NULL)
		{
			value_size += ((t_dict_content *)cursor->content)->value_size;
			cursor = cursor->next;
		}
		i++;
	}
	return (value_size);
}

size_t calculate_total_size(t_hashmap_struct *hashmap)
{
	size_t value_size;
	size_t target_size;

	value_size = calculate_total_value_size(hashmap->dict_chain);
	target_size = calculate_total_target_size(hashmap);
	return (target_size + value_size);
}
