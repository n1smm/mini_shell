/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:16:53 by thiew             #+#    #+#             */
/*   Updated: 2024/09/26 12:44:30 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

static void	check_it_out(t_token *curr, int *pipe, int *command)
{
	while (curr)
	{
		if (curr->typ_token == PIPELINE)
			*pipe = 1;
		else if (*pipe == 1 && curr->typ_token != PIPELINE
			&& curr->typ_token != WHITESPACE)
			*command = 1;
		curr = curr->next;
	}
}

int	check_pipe(t_token **tail, t_type file_type[])
{
	t_token	*curr;
	int		pipe;
	int		command;
	int		i;

	curr = *tail;
	pipe = 0;
	command = 0;
	i = -1;
	check_it_out(curr, &pipe, &command);
	while (file_type[++i] != NONPRINTABLE)
	{
		if (file_type[i] == REDIRECT_OUT || file_type[i] == REDIRECT_OUT_DOUBLE)
			command = 0;
	}
	if (pipe == 1 && command == 1)
		return (1);
	if (pipe == 1 && command == 0)
		return (-1);
	return (0);
}

int	execute_single(char **input, t_shell *data, t_token **tail, t_token **head)
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
	else
		return (2);
}

int	is_builtin(char **input)
{
	if (!input[0])
		return (0);
	if (ft_strncmp(input[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(input[0], "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(input[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(input[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(input[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(input[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(input[0], "echo", 5) == 0)
		return (1);
	return (0);
}

void	free_here(t_shell *data, t_token **tail, char **comm_seq)
{
	t_token	*curr;
	t_token	*tmp;

	curr = *tail;
	while (curr && curr->next)
	{
		tmp = curr->next;
		free(curr->content);
		free(curr);
		curr = tmp;
	}
	if (curr)
	{
		if (curr->content)
			free(curr->content);
		free(curr);
	}
	if (comm_seq)
		free_mtrx(comm_seq);
	close(data->pipefd[2]);
	close(data->pipefd[3]);
	free_garbage(&data->garbage);
}
