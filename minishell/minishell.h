/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:46:03 by thiew             #+#    #+#             */
/*   Updated: 2024/05/21 17:35:36 by thiew            ###   ########.fr       */
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

typedef struct s_input
{
	char			**tokens;
}					t_input;

typedef enum s_type
{
	WHITESPACE,
	NUMBER,
	WORD,
	PIPELINE,
	REDIRECT_IN,
	REDIRECT_OUT,
	EXPAND,
	COMMAND,
	OPTION,
}					t_type;

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
/* safe_functions */
void				*safe_malloc(size_t size);
/*split_input*/
void				split_input(char *input);
bool				term_character(char c);
char				*ft_chardup(char character);
/*list functions*/
void				ft_add_token(char *word);
void				ft_add_token2(char character);
/* make_list */
t_token				*init(char *content, t_token **tail, t_token **head);
bool				double_lstadd_front(char *content, t_token **tail);
bool				double_lstadd_back(char *content, t_token **head);
void				print_list(t_token *tail);
/* path_finder */
char				*path_finder(char *command);
/* free_functions */
void				free_mtx(void **matrix);

#endif
