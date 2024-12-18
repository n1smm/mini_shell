/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:46:03 by thiew             #+#    #+#             */
/*   Updated: 2024/09/27 18:50:42 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "executor/gnl_finished/get_next_line.h"
# include "includes/structs.h"
# include "libft/libft.h"
# include <dirent.h>
# include <dlfcn.h>
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

/* utils_main */
char	*ft_strdup_exp(const char *s);
void	ft_init_shell(t_shell **data, char **env);
size_t	count_env_vars(char **env);

/* safe_functions */
void	*safe_malloc(size_t size);
char	*join_wrapper(const char *s1, const char *s2, int free_which);
char	*create_empty_string(int len);
int		safe_dup(int old_fd, int new_fd, int which);
int		safe_open(char *pathname, int flags, mode_t mode);
/* utils tokens */
int		is_delimiting_node(t_token *curr);
int		is_delimiting_type(t_type type);
int		is_quote_node(t_token *curr);
bool	is_redirect(t_token *curr);
bool	is_file(t_token *curr);
/*split_input*/
void	split_input(char *input, t_token **head);
bool	term_character(char c);
char	*ft_chardup(char character);
/*parser*/
void	parser(t_token **tail, t_token **head, t_shell *data);
/* after_parsy */
int		after_parsy(t_token **tail, t_token **head);
/*executor*/
void	ft_executor(t_shell *data, t_token **token, char *args, char **env);
/*list functions*/
void	ft_add_token(const char *word, size_t end, t_type type, t_token **head);
void	ft_add_token2(char character);
/* make_list */
t_token	*init(char *content, t_token **tail, t_token **head);
bool	double_lstadd_front(char *content, t_token **tail);
bool	double_lstadd_back(char *content, t_token **head);
t_token	*delete_node2(t_token **tail, t_token **del, t_token **head);
void	delete_node(t_token **tail, t_token *del, t_token **head);
char	*use_token(t_token **tail, t_type type);
int		find_token(t_token *tail, t_type type);
/* path_finder */
char	*path_finder(char *command, t_shell *data);
bool	correct_path(char *command, t_shell *data);
/*expander*/
char	*custom_getenv(char *name, char **env);
void	expand_checker(t_token *curr, t_shell *var);
char	*expander(char *input, t_shell *var, t_type typ_token);
// char				*expander(char *input, t_type typ_token);
char	*expand_string_checker(char *content, t_shell *var, bool special_boy);
/* free_functions */
void	free_mtx(void **matrix);
void	free_tokens(t_token **tail, t_token **head);
void	free_tokens_final(t_token **tail, t_token **head);
void	error_handling(char *msg, int error_code);
/* built-ins */
bool	ft_cd(const char *path, char **input);
void	ft_echo(char **args);
void	ft_env(t_shell *var);
int		ft_pwd(void);
int		ft_unset(t_shell *var, char **args);
int		ft_exit(t_shell *data, char **comm_seq, t_token **tail, t_token **head);

// EXPAND
void	expand_checker(t_token *curr, t_shell *var);
// EXPAND UTILS
char	*ref_expand_str(char *content, t_shell *var, int start, int len);
void	refurbish_node(t_token *curr, char *content);
void	check_len(char *content, int *j);
// EXPORT
void	ft_export(t_shell *var, char **args);
// EXPORT UTILS
int		check_env_var(char *str, int index);
char	*ft_strjoin_exp(char const *s1, char const *s2);
// ADD TO ENV
void	add_to_env(t_shell *var, char *new_var);
int		valid_env_var(char *args);
// ADD TO EXPORT
void	add_to_export(t_shell *var, char *new_var);
void	add_to_export2(t_shell *var, char *new_var);
void	add_to_export2_supp(t_shell *var, int *i, const char *new_var);

// AFTER PARSY

// AFTER PARSY UTILS
int		check_quotes(t_token **tail);
int		check_eol(t_token **tail);

// UNSET EXP
void	unset_var_exp(const char *unset_var, t_shell *var);

// PARSER_UTILS
void	check_string(t_token *curr, t_type *mod_type, int is_quote);
void	parsing_tokens(t_token *curr, t_type *mod_type);
t_token	*check_quote(t_token **tail, t_token *tmp, t_shell *data,
			t_type *mod_type);
void	str_or_word(t_token *curr, t_type *mod_type, int is_quote);
t_token	*return_node(t_token *curr, t_token *tmp);

t_type	quote_init(t_token *tmp, t_token **curr, int *is_quote,
			t_type *mod_type);

void	check_word(t_token *curr, t_type *mod_type, int is_quote);
void	expand_parser(t_token *curr, t_type *mod_type);
int		quote_parsing(t_token **curr, t_type *mod_type, t_token **tail,
			t_shell *data);
void	expand_parser(t_token *curr, t_type *mod_type);

void	check_word(t_token *curr, t_type *mod_type, int is_quote);

/*signals*/
void	catch_signals(void);
void	ctrl_c(int sig);
void	ctrl_d(int sig);
void	ctrl_slash(int sig);
void	free_input_prompt(char *input, char *prompt);
/* garbage collector */
void	init_garbage(t_trash *garbage);

void	add_to_garbage(t_token *garbage, void *trash);
void	add_to_garbage2(t_trash *garbage, void *trash);
void	free_garbage(t_token *garbage);

void	free_garbage_tail(t_token *garbage);

void	free_garbage2(t_trash *garbage);
void	free_garbage_shell(t_shell *garbage);
void	safe_exit(t_token *garbage, int i);

char	**seq_extract(t_token **tail);

int		eq_len(char *str);

void	ft_ls(void);
#endif
