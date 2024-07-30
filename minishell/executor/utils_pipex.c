/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:02:43 by tjuvan            #+#    #+#             */
/*   Updated: 2024/07/25 14:43:17 by thiew            ###   ########.fr       */
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
		printf("Comm seq : %s\n", comm_seq[0]);
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


void files_open(int file[], t_type file_type[], t_token **tail, int pipefd[])
{
	int		i;
	t_token	*curr;
	
	i = 0;
	curr = *tail;
	while (curr && curr->typ_token != PIPELINE)
	{
		if (curr->typ_token == REDIRECT_IN_DOUBLE)
		{	
			dup2(pipefd[2], 0);
			file[i] = create_heredoc(i, 1);
			file_type[i++] = REDIRECT_IN_DOUBLE;
		}
		else if (curr->typ_token == REDIRECT_IN)
		{
			dup2(pipefd[2], 0);
			file[i] = open(curr->next->content, O_RDONLY, 0777);
			file_type[i++] = REDIRECT_IN;
		}
		curr = curr->next;
	}
	out_files(file, file_type, tail, i);
}

static void	dup_last_file(int file[], t_type file_type[], int i, int io)
{
	int in;
	int	out;
	int	tmp;

	in = 0;
	out = 0;
	tmp = i;
	while (file_type[++i] != NONPRINTABLE)
	{
		if (file_type[i] == REDIRECT_IN || file_type[i] == REDIRECT_IN_DOUBLE)
			in = 1;
		if (file_type[i] == REDIRECT_OUT || file_type[i] == REDIRECT_OUT_DOUBLE)
			out = 1;
	}
	if (io == 0 && in == 0)
		dup2(file[tmp], STDIN_FILENO);
	if (io == 1 && out == 0)
		dup2(file[tmp], STDOUT_FILENO);
}

void	redirect_infiles(int file[], t_type file_type[], t_token **tail)
{
	int		i;
	t_token	*curr;

	i = 0;
	curr = *tail;
	while (file_type[i] != NONPRINTABLE)// && file_type[i] != REDIRECT_OUT && file_type[i] != REDIRECT_OUT_DOUBLE)
	{
		if (file_type[i] == REDIRECT_IN)
			dup_last_file(file, file_type, i, 0);
			/* dup2(file[i], STDIN_FILENO); */
			//CHECK ERROR
		if (file_type[i] == REDIRECT_IN_DOUBLE)
		{
			here_doc_redirect(file, &curr, i);
			dup_last_file(file, file_type, i, 0);
		}
		if (file_type[i] == REDIRECT_OUT || file_type[i] == REDIRECT_OUT_DOUBLE)
			dup_last_file(file, file_type, i, 1);
			/* dup2(file[i], STDOUT_FILENO); */
			//CHECK ERROR
		i++;
	}
}
