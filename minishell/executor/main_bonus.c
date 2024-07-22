/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:19:41 by thiew             #+#    #+#             */
/*   Updated: 2024/07/22 13:26:04 by tjuvan           ###   ########.fr       */
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


char	**pipe_loop(t_token **tail)
{
	char	*path;
	char	**command_seq;

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
	t_token		*tmp;
	char		**comm_seq;
	int i;
	/* char		**last; */

	/* last = NULL; */
	/* here_doc(file, tail); */
	/* if (dup2(file[0], STDIN_FILENO) == -1) */
	/* 	pid_error("dup in main failed", NULL, 0); */
	tmp = *tail;
	while (*tail) // || (*tail)->typ_token != REDIRECT_OUT || (*tail)->typ_token != REDIRECT_OUT_DOUBLE)
	{
		i = 0;
		files_open(file, file_type, tail);
		redirect_infiles(file, file_type, tail);
		comm_seq = pipe_loop(tail);
		while (comm_seq[i])
		{
			printf("comm_seq[%d]: %s \n", i, comm_seq[i]);
			i++;
		}
		envp = envp;
		comm_forker(comm_seq , envp, pipefd);
		if ( *tail && (*tail)->typ_token == PIPELINE)
			*tail = (*tail)->next;

	}
	*tail = tmp;
	/* close(file[0]); */
	/* unlink_doc(*tail); */
	/* last = ft_split(seq_extract(tail), ' '); */
	/* if (dup2(file[1], STDOUT_FILENO) == -1) */
	/* 	pid_error("outfile dup failed", NULL, 0); */
	/* execve(path_finder(last[0]), last, envp); */
	/* free_mtrx(last); */
	pid_error("last exec failed", NULL, 0);
	return(0);
}
