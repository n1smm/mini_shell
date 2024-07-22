/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:58:34 by tjuvan            #+#    #+#             */
/*   Updated: 2024/07/22 13:03:09 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PIPEX_H
# define PIPEX_H

#include "../minishell.h"
#include "./gnl_finished/get_next_line.h"

#define CURRENT_COMMAND (curr && curr->typ_token != REDIRECT_IN && \
		curr->typ_token != REDIRECT_IN_DOUBLE && \
		curr->typ_token != REDIRECT_OUT && \
		curr->typ_token != REDIRECT_OUT_DOUBLE && \
		curr->typ_token != PIPELINE)

/* typedef struct s_token t_token; */
/* typedef enum s_type	t_type; */

/* main */
int		executor(t_token **tail, char **envp);
char	**pipe_loop(t_token **tail);
void	pid_error(char *msg, char **str, int free_me);
void	free_mtrx(char **mtrx);
/* path_finder */
char	*read_path(int pipefd[], char **mtrx);
// char	*path_finder(char *command, char **mtrx);
/* utils */
void	comm_forker(char **comm_seq, char **envp, int pipefd[]);
/* void	files_open(int file[], t_token **tail); */
void 	files_open(int file[], t_type file_type[], t_token **tail);
void	redirect_infiles(int file[], t_type file_type[], t_token **tail);
/* utils_bonus */
void	here_doc(int file[], t_token **tail);
void	unlink_doc(t_token *tail);
/* sequence_extraction */
char 	**seq_extract(t_token **tail);
#endif
