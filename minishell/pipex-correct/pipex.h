/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:58:34 by tjuvan            #+#    #+#             */
/*   Updated: 2024/04/08 19:19:16 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./final_libft/libft.h"
#include "./gnl_finished/get_next_line.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/* main */
void	pipe_loop(char **last, int i, char **argv);
void	pid_error(char *msg, char **str, int free_me);
void	free_mtrx(char **mtrx);
/* path_finder */
char	*read_path(int pipefd[], char **mtrx);
char	*path_finder(char *command, char **mtrx);
/* utils */
void	comm_forker(char *str1, char **envp, int pipefd[]);
void	files_open(int file[], int argc, char **argv, int *i);
/* utils_bonus */
void	here_doc(int file[], char **argv);
void	unlink_doc(char **argv);
