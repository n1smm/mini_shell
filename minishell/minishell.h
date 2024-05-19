/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:46:03 by thiew             #+#    #+#             */
/*   Updated: 2024/05/19 13:47:22 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_input
{
	char	**tokens;
}			t_input;

typedef struct s_token
{
	t_type	typ_token;
	/* void 	*value; */
	char	*value;
	long	value;
	t_token	*next;
	t_token	*previous;
}			t_token;

typedef struct s_trash
{
	void	*content;
	t_trash	*next;
}			t_trash;
}
typedef enum s_type
{
	DIGIT,
	ALPHA,
	NUMBER,
	WORD,
	PIPELINE,
	REDIRECT,
	EXPAND,
	COMMAND,
	OPTION,
}			t_type;

/* lexer */
void		lexer_main(char *input);
/* safe_functions */
void		*safe_malloc(size_t size);
