/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:02:43 by tjuvan            #+#    #+#             */
/*   Updated: 2024/07/24 00:29:23 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

void	comm_forker(char **comm_seq, char **envp, int pipefd[], int is_pipe)
{
	pid_t	pid;

	if (pipe(pipefd) == -1)
		pid_error("forker;pipe failed", NULL, 1);
	pid = fork();
	if (pid == -1)
		pid_error("forker;fork failed", NULL, 1);
	if (pid == 0)
	{
		close(pipefd[0]);
		if (is_pipe)
		{
			dup2(pipefd[1], STDOUT_FILENO);
		}
		execve(path_finder(comm_seq[0]), comm_seq, envp);
		close(pipefd[1]);
		pid_error("forker;child failure", NULL, 1);
	}
	else
	{
		wait(NULL);
		close(pipefd[1]);
		free_mtrx(comm_seq);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			pid_error("forker;parent dup failed", NULL, 0);
	}
	/* if (pid == 0) */
	/* { */
	/* 	close(pipefd[0]); */
	/* 	if (is_pipe) */
	/* 		dup2(pipefd[1], STDOUT_FILENO); */
	/* 	/1* else *1/ */
	/* 	/1* { *1/ */
	/* 	/1* 	close(pipefd[1]); *1/ */
	/* 	/1* 	dup2(pipefd[0], STDIN_FILENO); *1/ */
	/* 	/1* } *1/ */
	/* 	close(pipefd[1]); */
	/* 	close(pipefd[1]); */
	/* 	pid_error("forker;child failure", NULL, 1); */
	/* } */
	/* else */
	/* { */
	/* 	close(pipefd[1]); */
	/* 	wait(NULL); */
	/* 	free_mtrx(comm_seq); */
	/* 	/1* if ((dup2(pipefd[0], STDIN_FILENO) == -1)) *1/ */
	/* 	/1* 		pid_error("forker;parent dup failed", NULL, 0); *1/ */
	/* } */
}

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

void	redirect_infiles(int file[], t_type file_type[], t_token **tail)
{
	int		i;

	i = 0;
	while (file_type[i] != NONPRINTABLE)// && file_type[i] != REDIRECT_OUT && file_type[i] != REDIRECT_OUT_DOUBLE)
	{
		if (file_type[i] == REDIRECT_IN)
			dup2(file[i], STDIN_FILENO);
			//CHECK ERROR
		if (file_type[i] == REDIRECT_IN_DOUBLE)
			here_doc(file,tail);
		if (file_type[i] == REDIRECT_OUT || file_type[i] == REDIRECT_OUT_DOUBLE)
			dup2(file[i], STDOUT_FILENO);
			//CHECK ERROR
		i++;
	}
}

	 /* int savedin dup(0) */
     /* int savedout dup1 */


	/* if < << dup2 fd stind */
	/* else if > >> dup2 fd out */

	/* dup2(savedin , 0 */ 
