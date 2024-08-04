/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:03:52 by tjuvan            #+#    #+#             */
/*   Updated: 2024/08/04 22:06:22 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

void	waiting_pids(t_token **tail, int builtin)
{
	t_token *curr;

	curr = *tail;
	if (!builtin)
		wait(NULL);
	while (curr)
	{
		if (curr->typ_token == PIPELINE)
			wait(NULL);
		curr = curr->next;
	}
}

void	execute_wrapper(char **comm_seq, t_shell *data)
{
	int	which_execute;

	which_execute = 0;
	close_doc(data->file, data->file_type, 1);
	which_execute = execute_comm(comm_seq, data);
	if (which_execute == 0)
	{
		if (execve(path_finder(comm_seq[0]), comm_seq, data->env) == -1)
			pid_error("execve failed", NULL, 1);
	}
	else if (which_execute == 2) 
	{
		if (execve(comm_seq[0], comm_seq, data->env) == -1)
			pid_error("execve failed", NULL, 1);
	}
	close(data->pipefd[1]);
}
