/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:46:03 by thiew             #+#    #+#             */
/*   Updated: 2024/07/09 22:47:42 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "pipex-changed/pipex.h"
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

typedef struct s_input
{
	char			**tokens;
}					t_input;
 enum s_type
{
	WHITESPACE,
	NONPRINTABLE,
	WORD,
	STRING,
	PIPELINE,
	REDIRECT_IN,
	REDIRECT_IN_DOUBLE,
	REDIRECT_OUT,
	REDIRECT_OUT_DOUBLE,
	QUOTE,
	SINGLE_QUOTE,
	EXPAND,
	PATH,
	COMMAND,
	OPTION,
	INFILE,
	OUTFILE,
	LIMITER,
	PRINTABLE,
	FALSE_PLACEMENT,
}					t_type;

typedef struct	s_shell
{
	bool	running;
}				t_shell;

typedef struct	s_dir
{
	char	*file_name;
}				t_dir;

typedef struct s_token
{
	t_type			typ_token;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_trash
{
	void			*content;
	void			*next;
}					t_trash;
/* lexer */
void				lexer_main(char *input);
void 				ft_lexer(t_token *token);
/* safe_functions */
void				*safe_malloc(size_t size);
char 				*join_wrapper(const char *s1, const char *s2, int free_which);
/*split_input*/
void				split_input(char *input, t_token **tail, t_token **head);
bool				term_character(char c);
char				*ft_chardup(char character);
/*parser*/
void				parser(t_token **tail, t_token **head);
/*executor*/
void				ft_executor(t_token **token);
/*list functions*/
void				ft_add_token(const char *word, size_t end, t_type type, t_token **head);
void				ft_add_token2(char character);
/* make_list */
t_token				*init(char *content, t_token **tail, t_token **head);
bool				double_lstadd_front(char *content, t_token **tail);
bool				double_lstadd_back(char *content, t_token **head);
long				find_token(t_token *tail, t_type type_to_find);
t_token				*use_token(t_token **tail, t_type type_to_find);
char 				*print_token_typ(t_type token_type);
void				print_list(t_token *tail);
/* path_finder */
char				*path_finder(char *command);
/*expander*/
void				expand_checker(t_token *curr);
char				*expander(char *input, t_type typ_token);
/* free_functions */
void				free_mtx(void **matrix);
void				free_tokens(t_token **tail, t_token **head, int	final_free);
/* built-ins */
bool				ft_cd(const char *path);
void				ft_echo(char *str);
bool				ft_env(void);
bool				ft_pwd(void);
bool				ft_unset(void);
/*signals*/
void				catch_signals();
void				ctrl_c(int sig);
void				ctrl_slash(int sig);

void ft_ls(void);
#endif
