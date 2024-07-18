/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:58:34 by tjuvan            #+#    #+#             */
/*   Updated: 2024/07/17 19:20:20 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "./gnl_finished/get_next_line.h"

typedef struct s_token t_token;

/* main */
int		executor(t_token **tail, char **envp);
char	*pipe_loop(t_token **tail);
void	pid_error(char *msg, char **str, int free_me);
void	free_mtrx(char **mtrx);
/* path_finder */
char	*read_path(int pipefd[], char **mtrx);
// char	*path_finder(char *command, char **mtrx);
/* utils */
void	comm_forker(char *str1, char **envp, int pipefd[]);
/* void	files_open(int file[], t_token **tail); */
void 	files_open(int file[], t_type file_type[], t_token **tail);
/* utils_bonus */
void	here_doc(int file[], t_token **tail);
void	unlink_doc(t_token *tail);
