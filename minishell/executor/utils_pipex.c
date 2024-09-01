/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:02:43 by tjuvan            #+#    #+#             */
/*   Updated: 2024/09/01 16:30:10 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

void	comm_forker(char **comm_seq, t_shell *data, int is_pipe, t_token **tail)
{
	pid_t	pid;

	if (pipe(data->pipefd) == -1)
		pid_error("forker;pipe failed", NULL, 1);
	pid = fork();
	if (pid == -1)
		pid_error("forker;fork failed", NULL, 1);	
	/* printf("pid of current process: %d\n", pid); */
	if (pid == 0)
	{
		close(data->pipefd[0]);
		if (data->file_type[0] != NONPRINTABLE)
			redirect_infiles(data, data->file, data->file_type, tail);
		if (is_pipe == 1)
		{
			safe_dup(data->pipefd[1], STDOUT_FILENO, 1);
		}
		else if (is_pipe == -1)
			safe_dup(data->pipefd[1], data->pipefd[3], 1);

		/* if (check_pipe(tail, file_type) == -1) */
		/* 	dup2(STDOUT_FILENO, pipefd[3]); */
		close_doc(data, data->file, data->file_type, 0);
		if (execute_comm(comm_seq, data) == 0)
			if (execve(path_finder(comm_seq[0], data), comm_seq, data->env) == -1)
				pid_error("execve failed", NULL, 1);
		close(data->pipefd[1]);
		exit(EXIT_SUCCESS);
		//pid_error("forker;child failure", NULL, 1);
	}
	else
	{
		if (find_file_type(data, REDIRECT_IN_DOUBLE))
			wait(NULL);
		close(data->pipefd[1]);
		/* free_mtrx(comm_seq); */
		if (safe_dup(data->pipefd[0], STDIN_FILENO, 1) == -1)
			pid_error("forker;parent dup failed", NULL, 0);
	}

}

int	out_files(t_shell *data, t_token **tail, int i)
{
	t_token *curr;

	curr = *tail;
	while(curr && curr->typ_token != PIPELINE)
	{
		if (curr->typ_token == REDIRECT_OUT)
		{
			while (curr && !is_file(curr))
				curr = curr->next;
			/* while (curr && is_file(curr)) */
			/* 	curr = curr->next; */
			data->file[i] = safe_open(curr->content, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (data->file[i] == -1)
				return (0);
			data->file_type[i++] = REDIRECT_OUT;
		}
		else if (curr->typ_token == REDIRECT_OUT_DOUBLE)
		{
			while (curr && !is_file(curr))
				curr = curr->next;
			data->file[i] = safe_open(curr->content, O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (data->file[i] == -1)
				return (0);
			data->file_type[i++] = REDIRECT_OUT_DOUBLE;
		}
		curr = curr->next;
	}
	data->file_type[i] = NONPRINTABLE;
	return (1);
}


int files_open(t_token **tail, t_shell *data)
{
	int		i;
	t_token	*curr;
	
	i = 0;
	curr = *tail;
	while (curr && curr->typ_token != PIPELINE)
	{
		if (curr->typ_token == REDIRECT_IN_DOUBLE)
		{	
			while (curr && !is_file(curr))
				curr = curr->next;
			safe_dup(data->pipefd[2], 0, 1);
			data->file[i] = create_heredoc(data, i, 1);
			data->file_type[i++] = REDIRECT_IN_DOUBLE;
		}
		else if (curr->typ_token == REDIRECT_IN)
		{
			while (curr && !is_file(curr))
				curr = curr->next;
			safe_dup(data->pipefd[2], 0, 1);
			data->file[i] = safe_open(curr->content, O_RDONLY, 0777);
			if (data->file[i] == -1)
				return (0);
			data->file_type[i++] = REDIRECT_IN;
		}
		curr = curr->next;
	}
	return (out_files(data, tail, i));
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
		safe_dup(file[tmp], STDIN_FILENO, 1);
	if (io == 1 && out == 0)
		safe_dup(file[tmp], STDOUT_FILENO, 1);
}

void	redirect_infiles(t_shell *data, int file[], t_type file_type[], t_token **tail)
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
			here_doc_redirect(data, &curr, i, curr->special_boy);
			dup_last_file(file, file_type, i, 0);
		}
		if (file_type[i] == REDIRECT_OUT || file_type[i] == REDIRECT_OUT_DOUBLE)
			dup_last_file(file, file_type, i, 1);
			/* dup2(file[i], STDOUT_FILENO); */
			//CHECK ERROR
		i++;
	}
}
