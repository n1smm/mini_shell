/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:19:41 by thiew             #+#    #+#             */
/*   Updated: 2024/06/24 19:45:05 by thiew            ###   ########.fr       */
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

char *seq_extract(t_token **tail)
{
	while (*tail ||(*tail)->typ_token != PIPELINE || (*tail)->typ_token != REDIRECT_OUT || (*tail)->typ_token != REDIRECT_OUT_DOUBLE)
	{
		//here we put the nodes into a string
	}

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
}

int	executor(t_token **tail, char **envp)
{
	int		pipefd[2];
	int		file[2];
	char	*last;
	int		i;

	last = NULL;
	files_open(file, tail, &i);
	here_doc(file, tail);
	if (dup2(file[0], STDIN_FILENO) == -1)
		pid_error("dup in main failed", NULL, 0);
	while (i < argc - 2)
	{
		last = pipe_loop(tail);
		comm_forker(argv[i++], envp, pipefd);
	}
	close(file[0]);
	unlink_doc(*tail);
	last = ft_split(argv[i], ' ');
	if (dup2(file[1], STDOUT_FILENO) == -1)
		pid_error("outfile dup failed", NULL, 0);
	execve(path_finder(last[0], last), last, envp);
	free_mtrx(last);
	pid_error("last exec failed", NULL, 0);
}
