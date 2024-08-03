/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:58:34 by tjuvan            #+#    #+#             */
/*   Updated: 2024/08/03 16:50:01 by tjuvan           ###   ########.fr       */
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
int		new_executor(t_token **tail, t_shell *data);
int		execute_comm(char **input, t_shell *data);
/* path_finder */
char	*read_path(int pipefd[], char **mtrx);
/* utils */
/* void	comm_forker(char **comm_seq, t_shell *data, int pipefd[], int is_pipe); */
void	comm_forker(char **comm_seq, t_shell *data, int pipefd[], int is_pipe, int file[], t_type file_type[], t_token **tail);
void 	files_open(int file[], t_type file_type[], t_token **tail, int pipefd[]);
void	redirect_infiles(int file[], t_type file_type[], t_token **tail);
/* utils_bonus */
void	here_doc(int file[], t_token **tail, int i, bool special_boy);
void	close_doc(int file[], t_type file_type[], int delete);
int		check_pipe(t_token **tail, t_type file_type[]);
int		create_heredoc(int j, int create);
void	here_doc_redirect(int file[], t_token **tail, int i, bool special_boy);
/* sequence_extraction */
char 	**seq_extract(t_token **tail);
/* utils mini */
void	waiting_pids(t_token **tail, int builtin);

#endif
