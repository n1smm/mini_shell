/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:02:43 by tjuvan            #+#    #+#             */
/*   Updated: 2024/08/03 14:09:22 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

void	comm_forker(char **comm_seq, t_shell *data, int pipefd[], int is_pipe, int file[], t_type file_type[], t_token **tail)
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
		if (file_type[0] != NONPRINTABLE)
			redirect_infiles(file, file_type, tail);
		if (is_pipe == 1)
		{
			dup2(pipefd[1], STDOUT_FILENO);
		}
		else if (is_pipe == -1)
			dup2(pipefd[1], pipefd[3]);

		/* if (check_pipe(tail, file_type) == -1) */
		/* 	dup2(STDOUT_FILENO, pipefd[3]); */
		printf("Comm seq : %s\n", comm_seq[0]);
		printf("%s\n", data->env[0]);
		printf("%s\n", data->env[20]);
		close_doc(file, file_type, 0);
		if (execute_comm(comm_seq, data) == 0)
			if (execve(path_finder(comm_seq[0]), comm_seq, data->env) == -1)
				pid_error("execve failed", NULL, 1);
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
		//pid_error("forker;child failure", NULL, 1);
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
			here_doc_redirect(file, &curr, i, curr->special_boy);
			dup_last_file(file, file_type, i, 0);
		}
		if (file_type[i] == REDIRECT_OUT || file_type[i] == REDIRECT_OUT_DOUBLE)
			dup_last_file(file, file_type, i, 1);
			/* dup2(file[i], STDOUT_FILENO); */
			//CHECK ERROR
		i++;
	}
}
