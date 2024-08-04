/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:46:03 by thiew             #+#    #+#             */
/*   Updated: 2024/08/03 18:01:28 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "includes/structs.h"
/* # include "executor/pipex.h" */
# include "executor/gnl_finished/get_next_line.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <dlfcn.h>

//int	exit_code;

/* lexer */
void				lexer_main(char *input);
void 				ft_lexer(t_token *token);
/* safe_functions */
void				*safe_malloc(size_t size);
char 				*join_wrapper(const char *s1, const char *s2, int free_which);
char				*create_empty_string(int len);
int				safe_dup(int old_fd, int new_fd, int which);
/* utils tokens */
int					is_delimiting_node(t_token *curr);
int					is_delimiting_type(t_type type);
/*split_input*/
void				split_input(char *input, t_token **tail, t_token **head);
bool				term_character(char c);
char				*ft_chardup(char character);
/*parser*/
void				parser(t_token **tail, t_token **head);
/* after_parsy */
void				after_parsy(t_token **tail, t_token **head);
/*executor*/
void	            ft_executor(t_shell *data, t_token **token, char *args, char **env);
/*list functions*/
void				ft_add_token(const char *word, size_t end, t_type type, t_token **head);
void				ft_add_token2(char character);
/* make_list */
t_token				*init(char *content, t_token **tail, t_token **head);
bool				double_lstadd_front(char *content, t_token **tail);
bool				double_lstadd_back(char *content, t_token **head);
void 				delete_node(t_token **tail, t_token *del);
t_token 			*use_token(t_token **tail, t_type type);
int					find_token(t_token *tail, t_type type);
char 				*print_token_typ(t_type token_type);
void				print_list(t_token *tail);
/* path_finder */
char				*path_finder(char *command);
/*expander*/
void				expand_checker(t_token *curr);
char				*expander(char *input, t_type typ_token);
char				*expand_string_checker(char *content, bool special_boy);
/* free_functions */
void				free_mtx(void **matrix);
//void				free_tokens(t_token **tail, t_token **head, int	final_free);
void                free_tokens(t_token *head);

/* built-ins */
bool				ft_cd(const char *path);
void				ft_echo(char **args);
void				ft_env(t_shell *var);
bool				ft_pwd(void);
void				ft_unset(t_shell *var, char **args);
void    			ft_export(t_shell *var, char **args);

/* env */
t_env_var             *init_env_vars(t_env_var **tail, t_env_var **head);
void 				ft_init_env(t_env_var **tail, t_env_var **head, char **env);
t_env_var			*env_new_node(t_env_var **tail, t_env_var **head, char **env);
char				**env_variables(t_env_var *vars);

/*signals*/
void				catch_signals();
void				ctrl_c(int sig);
void				ctrl_slash(int sig);

/* garbage collector */
void    init_garbage(t_trash *garbage);

void    add_to_garbage(t_token *garbage, void *trash);
void    free_garbage(t_token *garbage);
void    safe_exit(t_token *garbage, int i);

char **seq_extract(t_token **tail);


void ft_ls(void);
#endif
