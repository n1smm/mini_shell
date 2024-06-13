/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:02:43 by tjuvan            #+#    #+#             */
/*   Updated: 2024/04/08 19:23:45 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		execve(path_finder(first[0], first), first, envp);
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

void	files_open(int file[], int argc, char **argv, int *i)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		file[0] = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		file[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
		*i = 3;
	}
	else
	{
		file[0] = open(argv[1], O_RDONLY, 0777);
		file[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		*i = 2;
	}
	if (file[1] == -1)
	{
		close(file[0]);
		pid_error("open of write end failed", NULL, 0);
	}
	if (file[0] == -1)
	{
		close(file[1]);
		pid_error("open of read end failed", NULL, 0);
	}
}
