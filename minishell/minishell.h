/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:46:03 by thiew             #+#    #+#             */
/*   Updated: 2024/05/19 16:29:38 by pgiorgi          ###   ########.fr       */
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
#include <stdbool.h>

typedef struct s_input
{
	char	**tokens;
}			t_input;

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

typedef struct s_token
{
	t_type	typ_token;
	// void 	*value;
	char	*str;
	long	nbr;
	struct s_token	*next;
	struct s_token	*prev;
}			t_token;

typedef struct s_trash
{
	void	*content;
	void	*next;
}			t_trash;


/* lexer */
void		lexer_main(char *input);
/* safe_functions */
void		*safe_malloc(size_t size);
/*split_input*/
void split_input(char *input);
bool term_character(char c);
char	*ft_chardup(char character);

/*list functions*/
void	ft_add_token(char *word);
void	ft_add_token2(char character);