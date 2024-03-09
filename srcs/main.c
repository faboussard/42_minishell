/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/22 12:10:15 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/inc/libft.h"
#include "lexer.h"


int main()
{
	const char *input = "ls -l $HOME";
	g_line_t g_line = lexer(input);

	printf("Tokens:\n");
	for (int i = 0; i < g_line.count; i++) {
		printf("Type: %d, Value: %s\n", g_line.tokens[i].type, g_line.tokens[i].value);
	}
	free_g_line(g_line);
	return 0;
}
