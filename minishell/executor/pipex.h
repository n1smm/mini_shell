/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:58:34 by tjuvan            #+#    #+#             */
/*   Updated: 2024/09/27 16:56:20 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../minishell.h"
# include "./gnl_finished/get_next_line.h"

/* main */
int		executor(t_token **tail, char **envp);
char	**pipe_loop(t_token **tail);
void	pid_error(char *msg, char **str, int free_me);
void	free_mtrx(char **mtrx);
int		new_executor(t_token **tail, t_shell *data, t_token **head);
/* comm_execution */
int		execute_comm(char **input, t_shell *data, t_token **tail,
			t_token **head);
int		execute_comm1(char **input, t_shell *data, t_token **tail,
			t_token **head);
void	execute_wrapper(char **comm_seq, t_shell *data, int is_pipe,
			t_token **tail);
void	init_fds(t_shell *data);
int		polish_pipes(t_shell *data, t_token **tail, t_token *tmp);
/* path_finder */
char	*read_path(int pipefd[], char **mtrx);
/* utils */
void	comm_forker(char **comm_seq, t_shell *data, int is_pipe,
			t_token **tail);
int		files_open(t_token **tail, t_shell *data);
void	redirect_infiles(t_shell *data, int file[], t_type file_type[],
			t_token **tail);
/* utils_bonus */
void	here_doc(t_shell *data, t_token **tail, int i, bool special_boy);
void	close_doc(t_shell *data, int file[], t_type file_type[], int delete);
int		create_heredoc(t_shell *data, int j, int create);
void	here_doc_redirect(t_shell *data, t_token **tail, int i,
			bool special_boy);
/* sequence_extraction */
char	**seq_extract(t_token **tail);
/* utils mini */
void	waiting_pids(t_token **tail, int builtin);
int		find_file_type(t_shell *data, t_type type);
int		count_pipes(t_token *curr);
void	close_and_free(t_shell *data, t_token **tail, char **comm_seq);
/* check_files */
void	check_files(t_token **tail, t_token **head);
/* utils_files */
void	redirect_in(t_token *curr, int *i, t_shell *data);
int		redirect_out(t_token *curr, int *i, t_shell *data);
int		init_files(t_token **tail, t_token **head, t_shell *data,
			char ***comm_seq);
/* utils_rest */
int		check_pipe(t_token **tail, t_type file_type[]);
int		execute_single(char **input, t_shell *data, t_token **tail,
			t_token **head);
int		is_builtin(char **input);
void	free_here(t_shell *data, t_token **tail, char **comm_seq);

#endif
