/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:03:52 by tjuvan            #+#    #+#             */
/*   Updated: 2024/04/05 13:36:53 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*read_path(int pipefd[], char **mtrx)
{
	char	*path;

	path = ft_calloc(256, 1);
	close(pipefd[1]);
	wait(NULL);
	if (read(pipefd[0], path, 256) == -1)
	{
		free_mtrx(mtrx);
		pid_error("finder path read failure", &path, 1);
	}
	if (path[0] == 0)
	{
		free_mtrx(mtrx);
		free(path);
		pid_error("command not found", &path, 1);
	}
	path[ft_strlen(path) - 1] = '\0';
	close(pipefd[0]);
	return (path);
}

void	which_init(char **which, char *command)
{
	which[0] = "which";
	which[1] = command;
	which[2] = NULL;
}

char	*path_finder(char *command, char **mtrx)
{
	int		pipefd[2];
	pid_t	pid;
	char	*path;
	char	*which[3];

	which_init(which, command);
	if (pipe(pipefd) == -1)
		pid_error("finder pipe failed", NULL, 0);
	pid = fork();
	if (pid == -1)
		pid_error("finder fork failed", NULL, 0);
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		if (execve("/usr/bin/which", which, NULL) == -1)
			pid_error("execve finder failure", NULL, 0);
	}
	else
	{
		path = read_path(pipefd, mtrx);
		if (path[0] == 0)
			exit(EXIT_FAILURE);
	}
	return (path);
}
