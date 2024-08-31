/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:03:52 by tjuvan            #+#    #+#             */
/*   Updated: 2024/08/31 15:45:20 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

void	exit_pid_status(pid_t pid, int status)
{
	if (pid > 0)
	{
		if (WIFEXITED(status))
			g_error_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_error_code = 128 + WTERMSIG(status);
	}
}

void	waiting_pids(t_token **tail, int builtin)
{
	t_token *curr;
	pid_t	pid;
	int		status;

	curr = *tail;
	if (!builtin)
	{
		pid = waitpid(-1, &status, 0);
		exit_pid_status(pid, status);
	}

		/* wait(NULL); */
	while (curr)
	{
		if (curr->typ_token == PIPELINE)
		{
			pid = waitpid(-1, &status, 0);
			exit_pid_status(pid, status);
			/* wait(NULL); */
		}
		curr = curr->next;
	}
}

void	execute_wrapper(char **comm_seq, t_shell *data)
{
	int	which_execute;

	which_execute = 0;
	close_doc(data, data->file, data->file_type, 1);
	which_execute = execute_comm(comm_seq, data);
	if (which_execute == 0 || which_execute == 2)
	{
		if (execve(path_finder(comm_seq[0], data), comm_seq, data->env) == -1)
			pid_error("execve failed", NULL, 1);
	}
	/* else if (which_execute == 2) */ 
	/* { */
	/* 	if (execve(comm_seq[0], comm_seq, data->env) == -1) */
	/* 		pid_error("execve failed", NULL, 1); */
	/* } */
	close(data->pipefd[1]);
}

int	count_pipes(t_token *curr)
{
	int	i;
	
	i = 0;
	while (curr)
	{
		if (curr->typ_token == PIPELINE)
			i++;
		curr = curr->next;
	}
	return (i);
}

int	find_file_type(t_shell *data, t_type type)
{
	int	i;

	i = -1;
	while (data->file_type[++i] != NONPRINTABLE)
	{
		if (data->file_type[i] == type)
			return (1);
	}
	return (0);
}
