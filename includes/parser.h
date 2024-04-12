/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2024/04/09 15:07:54 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "minishell.h"

/************************** parser  **************************/

int parse_input(t_minishell *minishell);
void	token_requalification(t_token_list *list_tokens);
int	ft_strnstr_and_check(const char *big, const char *little, size_t len);
char	**ft_split_with_quotes_management(t_minishell *minishell, char *s);
char **fill_array_with_quotes_management(char *s);
void	*ft_free_all_alloc(char **strs_array, size_t start);
void deal_double_double_quotes_or_double_single_quotes(char *string);
size_t	count_letters_for_quotes( char *str);
size_t	count_letters_for_space( char *str);

/**************************** count tokens **************************/

size_t			count_letters_until_pipe_or_redirect(t_token_list *head);
size_t			count_cmds_until_pipe_or_redirect(t_token_list *head);

/**************************** parse tokens **************************/

void			create_process_list(t_minishell *minishell);
t_process_list	*create_process_list_node(t_process_list *new_process_list,
					t_minishell *minishell);
void			create_envp_table(t_minishell *minishell);

/****************** OPERATORS ******************/

bool			get_operator_token(t_token_list *new_token, char *string);
bool			is_redirect_token(t_token_list *token);

/******************** init.c **********************/
void			parsing(t_minishell *minishell, int ac, char **av, char **envp);

/********************* envp.c **************************/
t_envp_list		*create_envp_list(char **envp, t_minishell *minishell);

/********************* expansion.c ****************************/
void expander(t_minishell *minishell);
void			expand_and_create_envp_table(t_minishell *minishell);
char *add_until_char(char *temp, char *string, int *i, char c);
void join_tokens(t_minishell *minishell, t_token_list **list);

/********************* check_syntax **************************/
size_t check_quotes(t_minishell *minishell);

#endif // PARSER_H
