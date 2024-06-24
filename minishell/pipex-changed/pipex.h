/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:58:34 by tjuvan            #+#    #+#             */
/*   Updated: 2024/06/24 19:36:29 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "./final_libft/libft.h"
#include "./gnl_finished/get_next_line.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/* main */
char	*pipe_loop(t_token **tail);
void	pid_error(char *msg, char **str, int free_me);
void	free_mtrx(char **mtrx);
/* path_finder */
char	*read_path(int pipefd[], char **mtrx);
char	*path_finder(char *command, char **mtrx);
/* utils */
void	comm_forker(char *str1, char **envp, int pipefd[]);
void	files_open(int file[], t_token **tail, int *i);
/* utils_bonus */
void	here_doc(int file[], t_token **tail);
void	unlink_doc(t_token *tail);
