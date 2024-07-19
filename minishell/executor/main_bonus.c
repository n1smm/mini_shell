/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:19:41 by thiew             #+#    #+#             */
/*   Updated: 2024/07/19 19:03:09 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

void	free_mtrx(char **mtrx)
{
	int	i;

	i = 0;
	while (mtrx[i] != 0)
	{
		free(mtrx[i]);
		i++;
	}
	free(mtrx);
}

void	pid_error(char *msg, char **str, int free_me)
{
	perror(msg);
	exit(EXIT_FAILURE);
	if (free_me == 1)
		free(*str);
}

char *seq_extract(t_token **tail)
{
	char	*command_seq;
	t_token	*curr;

	curr = *tail;
	command_seq = safe_malloc(1);
	command_seq[0] = 0;
	while (curr && curr->typ_token != PIPELINE)// || curr->typ_token != REDIRECT_OUT || curr->typ_token != REDIRECT_OUT_DOUBLE)
	{
		command_seq = join_wrapper(command_seq, curr->content, 1);
		command_seq = join_wrapper(command_seq, " ", 1);
		curr = curr->next;
		*tail = (*tail)->next;
	}
	return (command_seq);
}

char	*pipe_loop(t_token **tail)
{
	char	*path;
	char	*command_seq;

	path = path_finder(use_token(tail, COMMAND)->content);
	if (path == NULL)
		pid_error("command not found", NULL, 0);
	free(path);
	command_seq = seq_extract(tail);
	return (command_seq);
}

int	executor(t_token **tail, char **envp)
{
	int			pipefd[2];
	int			file[1024];
	t_type		file_type[1024];
	char		*comm_seq;
	char		**last;

	/* last = NULL; */
	/* here_doc(file, tail); */
	/* if (dup2(file[0], STDIN_FILENO) == -1) */
	/* 	pid_error("dup in main failed", NULL, 0); */
	while (*tail) // || (*tail)->typ_token != REDIRECT_OUT || (*tail)->typ_token != REDIRECT_OUT_DOUBLE)
	{
		files_open(file, file_type, tail);
		redirect_infiles(file, file_type, tail);
		comm_seq = pipe_loop(tail);
		comm_forker(comm_seq , envp, pipefd);
		if ((*tail)->typ_token == PIPELINE)
			*tail = (*tail)->next;

	}
	close(file[0]);
	unlink_doc(*tail);
	last = ft_split(seq_extract(tail), ' ');
	if (dup2(file[1], STDOUT_FILENO) == -1)
		pid_error("outfile dup failed", NULL, 0);
	execve(path_finder(last[0]), last, envp);
	free_mtrx(last);
	pid_error("last exec failed", NULL, 0);
	return(0);
}
