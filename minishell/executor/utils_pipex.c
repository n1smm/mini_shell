/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:02:43 by tjuvan            #+#    #+#             */
/*   Updated: 2024/07/19 18:43:22 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

void	comm_forker(char *str1, char **envp, int pipefd[])
{
	pid_t	pid;
	char	**first;

	first = ft_split(str1, ' ');
	if (pipe(pipefd) == -1)
		pid_error("forker;pipe failed", NULL, 1);
	pid = fork();
	if (pid == -1)
		pid_error("forker;fork failed", NULL, 1);
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		execve(path_finder(first[0]), first, envp);
		close(pipefd[1]);
		pid_error("forker;child failure", NULL, 1);
	}
	else
	{
		close(pipefd[1]);
		free_mtrx(first);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			pid_error("forker;parent dup failed", NULL, 0);
	}
}

/* void	files_open(int file[], t_token **tail) */
/* { */
/* 	if (find_token(*tail, REDIRECT_IN_DOUBLE)) */
/* 		file[0] = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0777); */
/* 	else if (find_token(*tail, REDIRECT_IN)) */
/* 			file[0] = open(use_token(tail, INFILE)->content, O_RDONLY, 0777); */
/* 	else */
/* 		dup2(STDIN_FILENO, file[0]); */
/* 	if (find_token(*tail, REDIRECT_OUT)) */
/* 			file[1] = open(use_token(tail, OUTFILE)->content, O_WRONLY | O_CREAT | O_TRUNC, 0666); */
/* 	else if (find_token(*tail, REDIRECT_OUT_DOUBLE)) */
/* 			file[1] = open(use_token(tail, OUTFILE)->content, O_WRONLY | O_CREAT | O_APPEND, 0666); */
/* 	else */
/* 		dup2(STDOUT_FILENO, file[1]); */
/* 	if (file[1] == -1) */
/* 	{ */
/* 		close(file[0]); */
/* 		pid_error("open of write end failed", NULL, 0); */
	/* } */
/* 	if (file[0] == -1) */
/* 	{ */
/* 		close(file[1]); */
/* 		pid_error("open of read end failed", NULL, 0); */
/* 	} */
/* } */

void	out_files(int file[], t_type file_type[], t_token **tail, int i)
{
	t_token *curr;
	//hello

	curr = *tail;
	while(curr && curr->typ_token != PIPELINE)
	{
		if (curr->typ_token == REDIRECT_OUT)
		{
			file[i] = open(curr->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			file_type[i++] = REDIRECT_OUT;
		}
		else if (curr->typ_token == REDIRECT_OUT_DOUBLE)
		{
			file[i] = open(curr->next->content, O_WRONLY | O_CREAT | O_APPEND, 0666);
			file_type[i++] = REDIRECT_OUT_DOUBLE;
		}
		curr = curr->next;
	}
	file_type[i] = NONPRINTABLE;
}

void files_open(int file[], t_type file_type[], t_token **tail)
{
	int		i;
	t_token	*curr;
	
	i = 0;
	curr = *tail;
	while (curr && curr->typ_token != PIPELINE)
	{
		if (curr->typ_token == REDIRECT_IN_DOUBLE)
		{	
			file[i] = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0777); //consequitve heredocs with diff names
			file_type[i++] = REDIRECT_IN_DOUBLE;
		}
		else if (curr->typ_token == REDIRECT_IN)
		{
			file[i] = open(curr->next->content, O_RDONLY, 0777);
			file_type[i++] = REDIRECT_IN;
		}
		curr = curr->next;
	}
	
	out_files(file, file_type, tail, i);
}

/* here is a place for a function */
void	redirect_infiles(int file[], t_type file_type[], t_token **tail)
{
	int		i;
	int		savedin;
	/* int		savedout; */

	i = 0;
	savedin = dup(0);
	//CHECK ERROR
	/* savedout = dup(1); */
	while (file_type[i] != NONPRINTABLE && file_type[i] != REDIRECT_OUT && file_type[i] != REDIRECT_OUT_DOUBLE)
	{
		if (file_type[i] == REDIRECT_IN)
			dup2(file[i], STDIN_FILENO);
			//CHECK ERROR
		if (file_type[i] == REDIRECT_IN_DOUBLE)
			here_doc(file,tail);	
		i++;
	}
	dup2(savedin, 0);
	//CHECK ERROR
	/* dup2(savedout, 1); */
}

	 /* int savedin dup(0) */
     /* int savedout dup1 */


	/* if < << dup2 fd stind */
	/* else if > >> dup2 fd out */

	/* dup2(savedin , 0 */ 
