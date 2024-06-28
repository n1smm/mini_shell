/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:46:03 by thiew             #+#    #+#             */
/*   Updated: 2024/06/28 13:51:04 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
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
# include <dlfcn.h>

typedef struct s_input
{
	char			**tokens;
}					t_input;

typedef enum s_type
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

typedef	enum s_typ_env
{
	SSH_AUTH_SOCK,
	SESSION_MANAGER,
	GNOME_TERMINAL_SCREEN,
	SSH_AGENT_PID,
	LANGUAGE,
	LANG,
	XDG_CURRENT_DESKTOP,
	IM_CONFIG_PHASE,
	XDG_GREETER_DATA_DIR,
	COLORTERM,
	LIBVIRT_DEFAULT_URI,
	GPG_AGENT_INFO,
	DESKTOP_SESSION,
	USER,
	XDG_MENU_PREFIX,
	XDG_SESSION_PATH,
	QT_IM_MODULE,
	NO_PROXY,
	HOME,
	DBUS_SESSION_BUS_ADDRESS,
	DOCKER_HOST,
	GTK_MODULES,
	XDG_CONFIG_DIRS,
	VTE_VERSION,
	JOURNAL_STREAM,
	XDG_SESSION_DESKTOP,
	KRB5CCNAME,
	GNOME_DESKTOP_SESSION_ID,
	MANAGERPID,
	QT_ACCESSIBILITY,
	XDG_SEAT_PATH,
	LOGNAME,
	GNOME_TERMINAL_SERVICE,
	PATH_2,
	XMODIFIERS,
	SHELL,
	XDG_SESSION_TYPE,
	no_proxy,
	DBUS_STARTER_BUS_TYPE,
	INVOCATION_ID,
	SHLVL,
	XAUTHORITY,
	GDM_LANG,
	DBUS_STARTER_ADDRESS,
	DISPLAY,
	TERM,
	GDMSESSION,
	XDG_SESSION_CLASS,
	PWD,
	OLDPWD,
}				t_typ_env; //49

typedef	struct s_env_var
{
	t_typ_env			typ_env;
	int					num;
	struct s_env_var	*next;
	struct s_env_var	*prev;
}				t_env_var;

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
void				ft_env(void);
bool				ft_pwd(void);
bool				ft_unset(void);
/* env */
void				ft_init_env(t_env_var **tail, t_env_var **head);
t_env_var			*env_new_node(t_env_var **tail, t_env_var **head);
char				**env_variables(void);
/*signals*/
void				catch_signals();
void				ctrl_c(int sig);
void				ctrl_slash(int sig);

void ft_ls(void);
#endif
