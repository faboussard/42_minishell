/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:43:37 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/19 09:43:37 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

void print_array(char **array)
{
	ft_printf("------------------- PRINT ARRAY ------------------------------------\n");
	int i;

	if (array == NULL)
	{
		ft_printf("no array to print\n");
		return;
	}
	i = 0;
	while (array[i] != NULL)
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
}

void print_token(t_node *list_tokens)
{
	t_node  *iterator;
	t_token *token;

	if (list_tokens == NULL)
	{
		ft_printf("no list to print\n");
		return;
	}
	ft_printf("----------------------- PRINT LIST -----------------------\n");
	iterator = list_tokens;
	while (iterator != NULL)
	{
		token = (t_token *)(iterator)->content;
		ft_printf("Name : %s, Type: %d, Builtin: %d, Operator: %d\n", token->name, token->e_type, token->e_builtin, token->e_operator);
		iterator = iterator->next;
	}
	ft_printf("\n");
}

void	print_envp_dict(t_dict envp_dict)
{
	int					i;
	t_node				*cursor;
	t_dict_content		*dict_content;

	ft_printf("--------------- Hashmap / dictionnary ---------------\n");
	i = HASHMAP_ARR_SIZE;
	int size = ft_hm_size(envp_dict);
	ft_printf("Size: %d\n", size);
	while (i-- > 0)
	{
		cursor = envp_dict[i];
		while (cursor != NULL)
		{
			dict_content = cursor->content;
			ft_printf("%s=%s\n", dict_content->target, (char *) dict_content->content);
			ft_printf("content size : %d, target size : %d\n", dict_content->content_size, dict_content->target_size);
			cursor = cursor->next;
		}
	}
}
