/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:03:52 by tjuvan            #+#    #+#             */
/*   Updated: 2024/09/03 13:15:35 by thiew            ###   ########.fr       */
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
	t_token	*curr;
	pid_t	pid;
	int		status;

	curr = *tail;
	if (!builtin)
	{
		pid = waitpid(-1, &status, 0);
		exit_pid_status(pid, status);
	}
	while (curr)
	{
		if (curr->typ_token == PIPELINE)
		{
			pid = waitpid(-1, &status, 0);
			exit_pid_status(pid, status);
		}
		curr = curr->next;
	}
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

void	close_and_free(t_shell *data, t_token **tail, char **comm_seq)
{
	close_doc(data, data->file, data->file_type, 0);
	if (*tail && (*tail)->typ_token == PIPELINE)
		*tail = (*tail)->next;
	free_mtrx(comm_seq);
}
