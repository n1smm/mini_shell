/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:19:41 by thiew             #+#    #+#             */
/*   Updated: 2024/07/21 21:03:42 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

#define CURRENT_COMMAND (curr && curr->typ_token != REDIRECT_IN && \
		curr->typ_token != REDIRECT_IN_DOUBLE && \
		curr->typ_token != REDIRECT_OUT && \
		curr->typ_token != REDIRECT_OUT_DOUBLE && \
		curr->typ_token != PIPELINE)

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

int	command_len(t_token **tail)
{
	int	i;
	t_token	*curr;

	i = 0;
	curr = *tail;
	while (CURRENT_COMMAND)
	{
		if ( curr->typ_token == WHITESPACE || curr->typ_token == PRINTABLE || curr->typ_token == NONPRINTABLE)
			i--;
		curr = curr->next;
		i++;
	}
	return(i);
}	

char	**comm_seq_init(t_token **tail)
{
	char	**command_seq;
	int		length;

	length = command_len(tail);
	printf("length: %d \n", length);
	command_seq = malloc(length +1);
	return (command_seq);
}

char **seq_extract(t_token **tail)
{
	char	**command_seq;
	char	*foo;
	t_token	*curr;
	int		i;

	i = 0;
	curr = *tail;
	command_seq = comm_seq_init(tail);
	foo = safe_malloc(1);
	foo[0] = 0;
	while (CURRENT_COMMAND)
	{
		if(curr->typ_token != WHITESPACE)
			foo = join_wrapper(foo, curr->content, 1);
		curr = curr->next;
		if (curr->typ_token == WHITESPACE)
		{
			command_seq[i++] = ft_strdup(foo);
			free(foo);
		}
	}
	if (foo && foo[0] != 0)
		command_seq[i++] = ft_strdup(foo);
	if (foo)
		free(foo);
	*tail = curr;
	command_seq[i] = 0;
	return (command_seq);
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
	/* int			pipefd[2]; */
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
		/* comm_forker(comm_seq , envp, pipefd); */
		if ((*tail)->typ_token == PIPELINE)
			*tail = (*tail)->next;

	}
	*tail = tmp;
	close(file[0]);
	unlink_doc(*tail);
	/* last = ft_split(seq_extract(tail), ' '); */
	if (dup2(file[1], STDOUT_FILENO) == -1)
		pid_error("outfile dup failed", NULL, 0);
	/* execve(path_finder(last[0]), last, envp); */
	/* free_mtrx(last); */
	pid_error("last exec failed", NULL, 0);
	return(0);
}
