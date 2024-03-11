/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                               		        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/11/22 12:10:15 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LEXER_H
#define MINISHELL_LEXER_H

typedef enum
{
	cd,
	echo,
	pwd,
	export,
	unset,
	env,
	exit
} e_token_builtin;

typedef enum
{
	ARGUMENT,
	COMMAND,
	ENVIRONMENT
} e_token_group;

typedef enum
{
	builtin,
	delimiter,
	redirect,
	pipe,
	path_env,
} e_token_type;

typedef struct s_token_group
{
	e_token_group	e_group;
	e_token_type	e_type;
} t_token_group;

typedef struct s_token
{
	t_token_group	group;
	struct s_token	*next;
	struct s_token	*prev;
	char			*content;
}	t_token;

#endif //MINISHELL_LEXER_H
