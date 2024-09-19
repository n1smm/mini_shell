/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:02:43 by tjuvan            #+#    #+#             */
/*   Updated: 2024/09/19 14:30:44 by thiew            ###   ########.fr       */
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
	if (pid == 0)
	{
		execute_wrapper(comm_seq, data, is_pipe, tail);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (find_file_type(data, REDIRECT_IN_DOUBLE))
			wait(NULL);
		close(data->pipefd[1]);
		if (safe_dup(data->pipefd[0], STDIN_FILENO, 1) == -1)
			pid_error("forker;parent dup failed", NULL, 0);
		close(data->pipefd[0]);
	}
}

int	out_files(t_shell *data, t_token **tail, int i)
{
	t_token	*curr;

	curr = *tail;
	while (curr && curr->typ_token != PIPELINE)
	{
		if (curr->typ_token == REDIRECT_OUT)
		{
			if (!redirect_out(curr, &i, data))
				return (0);
		}
		else if (curr->typ_token == REDIRECT_OUT_DOUBLE)
		{
			while (curr && !is_file(curr))
				curr = curr->next;
			data->file[i] = safe_open(curr->content,
					O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (data->file[i] == -1)
				return (0);
			data->file_type[i++] = REDIRECT_OUT_DOUBLE;
		}
		curr = curr->next;
	}
	data->file_type[i] = NONPRINTABLE;
	return (1);
}

int	files_open(t_token **tail, t_shell *data)
{
	int		i;
	t_token	*curr;

	i = 0;
	curr = *tail;
	while (curr && curr->typ_token != PIPELINE)
	{
		if (curr->typ_token == REDIRECT_IN_DOUBLE)
			redirect_in(curr, &i, data);
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
	int	in;
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

void	redirect_infiles(t_shell *data, int file[], t_type file_type[],
		t_token **tail)
{
	int		i;
	t_token	*curr;

	i = 0;
	curr = *tail;
	while (file_type[i] != NONPRINTABLE)
	{
		if (file_type[i] == REDIRECT_IN)
			dup_last_file(file, file_type, i, 0);
		if (file_type[i] == REDIRECT_IN_DOUBLE)
		{
			here_doc_redirect(data, &curr, i, curr->special_boy);
			dup_last_file(file, file_type, i, 0);
		}
		if (file_type[i] == REDIRECT_OUT || file_type[i] == REDIRECT_OUT_DOUBLE)
			dup_last_file(file, file_type, i, 1);
		i++;
	}
}
