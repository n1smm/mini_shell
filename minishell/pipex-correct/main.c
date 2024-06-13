/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:19:41 by thiew             #+#    #+#             */
/*   Updated: 2024/04/05 13:39:15 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	pipe_loop(char **last, int i, char **argv)
{
	char	*path;

	last = ft_split(argv[i], ' ');
	path = path_finder(last[0], last);
	if (ft_strlen(path) == 0)
	{
		free_mtrx(last);
		pid_error("command not found", NULL, 0);
	}
	free_mtrx(last);
	free(path);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	int		file[2];
	char	**last;
	int		i;

	last = NULL;
	if (argc != 5)
		pid_error("wrong nr. of arguments", NULL, 0);
	files_open(file, argc, argv, &i);
	if (dup2(file[0], STDIN_FILENO) == -1)
		pid_error("dup in main failed", NULL, 0);
	while (i < argc - 2)
	{
		pipe_loop(last, i, argv);
		comm_forker(argv[i++], envp, pipefd);
	}
	close(file[0]);
	last = ft_split(argv[i], ' ');
	if (dup2(file[1], STDOUT_FILENO) == -1)
		pid_error("outfile dup failed", NULL, 0);
	execve(path_finder(last[0], last), last, envp);
	free_mtrx(last);
	pid_error("last exec failed", NULL, 0);
}
