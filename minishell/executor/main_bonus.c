/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:19:41 by thiew             #+#    #+#             */
/*   Updated: 2024/07/30 17:42:15 by thiew            ###   ########.fr       */
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
	{
		pid_error("command not found", NULL, 0);
	}
	free(path);
	command_seq = seq_extract(tail);
	return (command_seq);
}

int	execute_comm(char **input, t_shell *data)
{
	if (ft_strncmp(input[0], "cd", 3) == 0)
	{
		ft_cd(input[1]);
		return (1);
	}
	if(ft_strncmp(input[0], "env", 3) == 0)
	{
		ft_env(data);
		return (1);
	}
	else if(ft_strncmp(input[0], "export", 6) == 0)
	{
		ft_export(data, input);
		return (1);
	}
	else if(ft_strncmp(input[0], "unset", 5) == 0)
	{
		ft_unset(data, input);
		return (1);
	}
	else if(ft_strncmp(input[0], "pwd", 3) == 0)
	{
		ft_pwd();
		return (1);
	}
	else if(ft_strncmp(input[0], "echo", 4) == 0)
	{
		ft_echo(input);
		return (1);
	}
	else
		return (0);
}

int	new_executor(t_token **tail, t_shell *data, char **envp)
{
	int			pipefd[4];
	int			file[1024];
	t_type		file_type[1024];
	t_token		*tmp;
	char		**comm_seq;

	data = data;
	tmp = *tail;
	pipefd[2] = dup(0);
	pipefd[3] = dup(1);
	while (*tail)
	{
		files_open(file, file_type, tail, pipefd);
		if (file_type[0] != PRINTABLE)
			redirect_infiles(file, file_type, tail);
		comm_seq = pipe_loop(tail);
		if (!execute_comm(comm_seq, data))
			comm_forker(comm_seq , envp, pipefd, check_pipe(tail, file_type));
		if ( *tail && (*tail)->typ_token == PIPELINE)
			*tail = (*tail)->next;
		/* if ((*tail)->typ_token == COMMAND) */
		/* 	execute_comm(*tail, input, data); */
	}
	dup2(pipefd[2], 0);
	dup2(pipefd[3], 1);
	*tail = tmp;
	return(0);
}

// /* old executor */
// int	old_executor(t_token **tail, char **envp)
// {
// 	int			pipefd[4];
// 	int			file[1024];
// 	t_type		file_type[1024];
// 	t_token		*tmp;
// 	char		**comm_seq;
// 	/* int i; */

// 	tmp = *tail;
// 	pipefd[2] = dup(0);
// 	pipefd[3] = dup(1);
// 	while (*tail) // || (*tail)->typ_token != REDIRECT_OUT || (*tail)->typ_token != REDIRECT_OUT_DOUBLE)
// 	{
// 		/* i = 0; */
// 		files_open(file, file_type, tail, pipefd);
// 		if (file_type[0] != PRINTABLE)
// 			redirect_infiles(file, file_type, tail);
// 		comm_seq = pipe_loop(tail);
// 		/* while (comm_seq[i]) */
// 		/* { */
// 		/* 	printf("comm_seq[%d]: %s \n", i, comm_seq[i]); */
// 		/* 	i++; */
// 		/* } */
// 		comm_forker(comm_seq , envp, pipefd, check_pipe(tail, file_type));
// 		if ( *tail && (*tail)->typ_token == PIPELINE)
// 			*tail = (*tail)->next;
// 	}
// 	/* if (dup2(file[0], STDOUT_FILENO) == -1) */
// 	/* 	pid_error("outfile dup failed", NULL, 0); */
// 	dup2(pipefd[2], 0);
// 	dup2(pipefd[3], 1);
// 	/* if (dup2(pipefd[0], STDOUT_FILENO) == -1) */
// 	/* 	pid_error("dup2 to stdout failed", NULL, 0); */
// 	/* close(pipefd[0]); */
// 	*tail = tmp;
// 	/* close(file[0]); */
// 	/* unlink_doc(*tail); */
// 	/* last = ft_split(seq_extract(tail), ' '); */
// 	/* if (dup2(file[1], STDOUT_FILENO) == -1) */
// 	/* 	pid_error("outfile dup failed", NULL, 0); */
// 	/* execve(path_finder(last[0]), last, envp); */
// 	/* free_mtrx(last); */
// 	/* pid_error("last exec failed", NULL, 0); */
// 	return(0);
// }
