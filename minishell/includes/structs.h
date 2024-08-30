/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:25:41 by thiew             #+#    #+#             */
/*   Updated: 2024/08/27 15:35:07 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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


extern int	g_error_code;

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
	//t_trash				*trash;
}					t_env_var;

typedef struct	s_dir
{
	char			*file_name;
}					t_dir;

typedef struct s_trash
{
	void			*content;
	void			*next;
}					t_trash;

typedef struct s_token
{
	t_type			typ_token;
	bool			special_boy;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
	t_trash			*trash;
	t_trash			*last_trash;
}					t_token;

typedef struct	s_shell
{
	bool			running;
	size_t			num_env_var;
	char			**env;
	char			*var_name;
	char			*var_value;
	int				nbr_pipes;
	int				pipefd[4];
	int				file[1024];
	t_type			file_type[1024];
	t_token			*token;
	t_token			garbage;
	struct s_shell	*next;
	t_trash			*trash;
}				t_shell;


#endif
