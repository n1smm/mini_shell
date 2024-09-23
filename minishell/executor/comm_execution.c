/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comm_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:52:38 by thiew             #+#    #+#             */
/*   Updated: 2024/09/23 10:31:25 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

void	execute_wrapper(char **comm_seq, t_shell *data, int is_pipe,
		t_token **tail)
{
	close(data->pipefd[0]);
	tail = tail;
	if (data->file_type[0] != NONPRINTABLE)
		redirect_infiles(data, data->file, data->file_type, tail);
	if (is_pipe == 1)
	{
		safe_dup(data->pipefd[1], STDOUT_FILENO, 1);
	}
	else if (is_pipe == -1)
		safe_dup(data->pipefd[1], data->pipefd[3], 1);
	close_doc(data, data->file, data->file_type, 0);
	if (execute_comm(comm_seq, data, NULL, NULL) == 0)
		if (execve(path_finder(comm_seq[0], data), comm_seq, data->env) == -1)
			pid_error("execve failed", NULL, 1);
	close(data->pipefd[1]);
}

int	execute_comm1(char **input, t_shell *data, t_token **tail, t_token **head)
{
	if (!input[0])
	{
		printf("command not found: No such file or directory\n");
		return (-1);
	}
	if (ft_strncmp(input[0], "cd", 3) == 0)
	{
		ft_cd(input[1], input);
		return (1);
	}
	else if (ft_strncmp(input[0], "exit", 5) == 0)
	{
		return (ft_exit(data, input, tail, head));
	}
	else if (ft_strncmp(input[0], "env", 4) == 0)
	{
		ft_env(data);
		return (1);
	}
	else if (ft_strncmp(input[0], "export", 7) == 0)
	{
		ft_export(data, input);
		return (1);
	}
	return (0);
}

int	execute_comm(char **input, t_shell *data, t_token **tail, t_token **head)
{
	int	whaa;

	whaa = execute_comm1(input, data, tail, head);
	if (whaa != 0)
		return (whaa);
	else if (ft_strncmp(input[0], "unset", 6) == 0)
		return (ft_unset(data, input));
	else if (ft_strncmp(input[0], "pwd", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp(input[0], "echo", 5) == 0)
	{
		ft_echo(input);
		return (1);
	}
	else if ((correct_path(input[0], data)))
		return (0);
	else if (ft_strchr(input[0], '/'))
		return (2);
	else
	{
		error_handling("command not found", 127);
		return (-1);
	}
}

int	polish_pipes(t_shell *data, t_token **tail, t_token *tmp)
{
	safe_dup(data->pipefd[2], 0, 1);
	safe_dup(data->pipefd[3], 1, 1);
	close(data->pipefd[2]);
	close(data->pipefd[3]);
	*tail = tmp;
	waiting_pids(tail, data->file[1023]);
	return (0);
}

void	init_fds(t_token **tmp, t_token **tail, t_shell *data)
{
	tmp = tmp;
	tail = tail;
	data->pipefd[2] = dup(0);
	data->pipefd[3] = dup(1);
	data->file[1023] = 0;
}
