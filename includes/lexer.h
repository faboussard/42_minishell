/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:26:16 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/13 16:26:32 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

enum e_token_builtin
{
	cd,
	echo,
	pwd,
	export,
	unset,
	env,
};

enum e_token_group
{
	ARGUMENT,
	COMMAND,
	ENVIRONMENT,
	OPERATOR
};

enum e_token_type
{
	builtin,
	delimiter,
	redirect,
	path_env
};

typedef struct s_token_group
{
	enum e_token_group	e_group;
	enum e_token_type	e_type;
}					t_token_group;

typedef struct s_token
{
	t_token_group	group;
	struct s_token	*next;
	struct s_token	*prev;
	char			*content;
}					t_token;

#endif //LEXER_H
