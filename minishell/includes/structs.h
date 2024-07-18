#ifndef STRUCTS_H
# define STRUCTS_H

// # include "libft/libft.h"
// # include "includes/minishell.h"
// /* # include "executor/pipex.h" */
// # include "executor/gnl_finished/get_next_line.h"
// # include <limits.h>
// # include <readline/history.h>
// # include <readline/readline.h>
// # include <signal.h>
# include <stdbool.h>
// # include <stddef.h>
// # include <stdio.h>
// # include <stdlib.h>
// # include <unistd.h>
// # include <termios.h>
// # include <dirent.h>
// # include <errno.h>
// # include <string.h>
// # include <sys/wait.h>
// # include <dlfcn.h>

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

typedef	struct s_env_var
{
	//t_typ_env			typ_env;
	int					num;
	char				**env;
	struct s_env_var	*next;
	struct s_env_var	*prev;
}				t_env_var;

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

typedef struct	s_shell
{
	bool	running;
	int		num_env_var;
	//char	**env;
	t_token *token;
}				t_shell;

typedef struct s_trash
{
	void			*content;
	void			*next;
}					t_trash;

// typedef	enum s_typ_env
// {
// 	SSH_AUTH_SOCK,
// 	SESSION_MANAGER,
// 	GNOME_TERMINAL_SCREEN,
// 	SSH_AGENT_PID,
// 	LANGUAGE,
// 	LANG,
// 	XDG_CURRENT_DESKTOP,
// 	IM_CONFIG_PHASE,
// 	XDG_GREETER_DATA_DIR,
// 	COLORTERM,
// 	LIBVIRT_DEFAULT_URI,
// 	GPG_AGENT_INFO,
// 	DESKTOP_SESSION,
// 	USER,
// 	XDG_MENU_PREFIX,
// 	XDG_SESSION_PATH,
// 	QT_IM_MODULE,
// 	NO_PROXY,
// 	HOME,
// 	DBUS_SESSION_BUS_ADDRESS,
// 	DOCKER_HOST,
// 	GTK_MODULES,
// 	XDG_CONFIG_DIRS,
// 	VTE_VERSION,
// 	JOURNAL_STREAM,
// 	XDG_SESSION_DESKTOP,
// 	KRB5CCNAME,
// 	GNOME_DESKTOP_SESSION_ID,
// 	MANAGERPID,
// 	QT_ACCESSIBILITY,
// 	XDG_SEAT_PATH,
// 	LOGNAME,
// 	GNOME_TERMINAL_SERVICE,
// 	PATH_2,
// 	XMODIFIERS,
// 	SHELL,
// 	XDG_SESSION_TYPE,
// 	no_proxy,
// 	DBUS_STARTER_BUS_TYPE,
// 	INVOCATION_ID,
// 	SHLVL,
// 	XAUTHORITY,
// 	GDM_LANG,
// 	DBUS_STARTER_ADDRESS,
// 	DISPLAY,
// 	TERM,
// 	GDMSESSION,
// 	XDG_SESSION_CLASS,
// 	PWD,
// 	OLDPWD,
// }				t_typ_env;
#endif