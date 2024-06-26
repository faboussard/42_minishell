/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2024/05/27 11:36:52 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/*************************token_list_utils**************************/

void		ft_list_remove_if_same_type(t_token_list **begin_list,
				void *data_ref, int (*cmp)());
void		ft_list_remove_if_same_op(t_token_list **begin_list, void *data_ref,
				int (*cmp)());
int			ft_lstsize_token(t_token_list *lst);

/************************* join_tokens.c **************************/

int			join_tokens(t_token_list **list);
void		join_between_quotes(t_minishell *minishell, t_token_list **list);
void		join_between_spaces(t_minishell *minishell, t_token_list **list);
void		join_between_quotes_handler(t_token_list **list,
				enum e_token_operators op, t_minishell *m);
char		*join_in_heredoc(t_token_list **list);
void		do_join_not_spaces(t_minishell *m, t_token_list **list);

/************************* join_tokens_utils.c **************************/

void		change_token_name(t_token_list **list, char *new_name);
int			check_if_more_tokens(t_token_list **list,
				enum e_token_operators op);

/************************* token_requlif.c **************************/

void		define_heredoc_and_append(t_minishell *minishell,
				t_token_list **list);
void		define_operators(t_token_list *list_tokens);
void		define_builtins(t_token_list *list_tokens);
void		to_infile_or_outfile(t_token_list *list_tokens);
void		arg_to_command(t_token_list *list_tokens);
void		dollar_to_command(t_token_list *list_tokens);

/************************** parser  **************************/

int			parse_input(t_minishell *m);
void		*ft_free_all_alloc(char **strs_array, size_t start);
void		token_rework(t_minishell *m);
int			cmp(int op1, int op2);
void		create_process_list(t_minishell *m, t_process_list **process_list);
void		create_process_list_node(t_process_list *new_pl, t_minishell *m);
void		create_cmd_table(t_process_list *new_pl,
				size_t size, t_minishell *m);
void		add_process_to_list(t_process_list **process_list,
				t_process_list *new_process);
void		create_envp_table(t_minishell *minishell);
void		skip_operator(t_token_list **list, enum e_token_operators op);
void		free_all(char *value, char *key);
void		join_tokens_safely(t_minishell *m,
				t_token_list **list, t_token_list *cpy);
void		replace_empty_name(t_minishell *m, t_token_list *iterator);

/****************** OPERATORS ******************/

bool		get_operator_token(t_token_list *new_token, char *string);
bool		is_redirect_token(t_token_list *token);

/********************* envp **************************/

t_envp_list	*create_envp_list(char **envp, t_minishell *minishell);
t_envp_list	*create_new_envp(char *target, char *content);
void		add_envp_to_list(t_envp_list **list_envp, t_envp_list *new_envp);
int			remove_env_var(t_envp_list **env, char *key);
void		remove_node_envp(t_envp_list **begin_list,
				t_envp_list *node_to_remove);
void		free_envp(t_envp_list *envp);
int			ft_lstsize_envp(t_envp_list *lst);
void		create_env_variable(char **envp, t_envp_list **list_envp,
				t_minishell *minishell);
int			add_new_envp(t_envp_list **list_envp, char *target, char *content);
bool		add_value_to_envp_list_if_valid(char **args,
				t_envp_list *env_variables, t_minishell *m, size_t index);
char		*join_equal_sign(char *key);
void		remove_and_add_envp(t_minishell *m, char *value, char *key);
void		create_3_env_variables(t_minishell *m);
void		assign_shell_and_shell_level(t_envp_list **env_vars,
				t_minishell *m);
char		*trim_equal_sign(char *key);

/********************* expansion ****************************/

void		expander(t_minishell *minishell, t_token_list **list,
				bool is_here_doc);
void		handle_delimitor(t_token_list **iterator);
char		*expand_sigil(char *string, t_minishell *minishell);
char		*expand_sign(char *string, char *temp);
int			check_special_char_after_expand(char *string, char *string2);
void		change_to_status(t_minishell *minishell,
				t_token_list *iterator);
char		*identify_envp_string(char *string, t_minishell *m);
void		define_to_delete_tokens(t_token_list *const *list);
void		change_to_expansion(t_minishell *m, t_token_list **list,
				char **expanded_string);
void		add_quotes_count(t_token_list *iterator, int *single_quote_count,
				int *double_quote_count);
void		update_quote_counts(t_token_list *token, int *single_quote_count,
				int *double_quote_count);
int			s_quote_after_d_quote_and_dollar(t_token_list **list,
				int single_quote_count, int double_quote_count);
char		*get_string(char *string, t_minishell *minishell,
				t_envp_list *iterator);
void		split_and_expand(t_minishell *m,
				t_token_list **list, char *string);
void		process_dollar(t_minishell *m,
				t_token_list **list, int squote_count, int dquote_count);
void		handle_dollar_files(t_minishell *m, t_token_list **list);
void		handle_dollar(t_minishell *m, t_token_list **iterator,
				int *squote_count, int *dquote_count);

/********************* check_syntax **************************/
bool		check_quotes(t_minishell *minishell);
bool		print_quote_syntax_error(enum e_token_operators operator);
bool		print_operator_syntax_error(t_token_list *token);

#endif // PARSER_H
