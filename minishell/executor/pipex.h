/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:58:34 by tjuvan            #+#    #+#             */
/*   Updated: 2024/08/05 18:41:02 by tjuvan           ###   ########.fr       */
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
char	**pipe_loop(t_token **tail, t_shell *data);
void	pid_error(char *msg, char **str, int free_me);
void	free_mtrx(char **mtrx);
int		new_executor(t_token **tail, t_shell *data, t_token **head);
int		execute_comm(char **input, t_shell *data);
/* path_finder */
char	*read_path(int pipefd[], char **mtrx);
/* utils */
/* void	comm_forker(char **comm_seq, t_shell *data, int pipefd[], int is_pipe); */
void	comm_forker(char **comm_seq, t_shell *data, int is_pipe, t_token **tail);
/* void 	files_open(int file[], t_type file_type[], t_token **tail, int pipefd[]); */
void 	files_open(t_token **tail, t_shell *data);
void	redirect_infiles(t_shell *data, int file[], t_type file_type[], t_token **tail);
/* utils_bonus */
void	here_doc(t_shell *data, t_token **tail, int i, bool special_boy);
void	close_doc(t_shell *data, int file[], t_type file_type[], int delete);
int		check_pipe(t_token **tail, t_type file_type[]);
int		create_heredoc(t_shell *data, int j, int create);
void	here_doc_redirect(t_shell *data, t_token **tail, int i, bool special_boy);
/* sequence_extraction */
char 	**seq_extract(t_token **tail);
/* utils mini */
void	waiting_pids(t_token **tail, int builtin);
void	execute_wrapper(char **comm_seq, t_shell *data);
int		find_file_type(t_shell *data, t_type type);
int		count_pipes(t_token *curr);

#endif
