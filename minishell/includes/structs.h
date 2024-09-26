/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:25:41 by thiew             #+#    #+#             */
/*   Updated: 2024/09/26 16:04:34 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include <stdlib.h>

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
	int					num;
	char				**env;
	struct s_env_var	*next;
	struct s_env_var	*prev;
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
	char			**exp;
	char			*var_name;
	char			*var_value;
	int				nbr_pipes;
	int				pipefd[4];
	int				file[1024];
	int				i;
	t_type			file_type[1024];
	t_token			*token;
	t_token			garbage;
	struct s_shell	*next;
	t_trash			*trash;
}				t_shell;

#endif
