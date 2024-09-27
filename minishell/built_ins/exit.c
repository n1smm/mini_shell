/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 22:21:25 by thiew             #+#    #+#             */
/*   Updated: 2024/09/19 12:50:45 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (i > 19)
		return (0);
	return (1);
}

void	get_exit_code(char **comm_seq)
{
	int	exit_code;

	if (!comm_seq[1])
		exit_code = 0;
	else if (is_number(comm_seq[1]))
		exit_code = ft_atoi(comm_seq[1]);
	else
	{
		exit_code = 255;
		write(STDERR_FILENO, "numeric argument required", 25);
	}
	g_error_code = exit_code;
	free_mtx((void **)comm_seq);
	exit(exit_code);
}

static int	exit_supp(t_shell *data, t_token **tail, t_token **head, char **comm_seq)
{
	close(data->pipefd[2]);
	close(data->pipefd[3]);
	free_tokens_final(tail, head);
	free_garbage(&(data->garbage));
	get_exit_code(comm_seq);
	return (1);
}

int	ft_exit(t_shell *data, char **comm_seq, t_token **tail, t_token **head)
{
	int i;

	i = 0;
	*data=*data;
	head = head;	
	write(STDERR_FILENO, "exit", 4);
	write(STDERR_FILENO, "\n", 1);
	if (comm_seq)
	{
		while(comm_seq[i])
			i++;
		if (i < 3)
		{
			if (tail)
				return (exit_supp(data, tail, head, comm_seq));
		}
		else
		{
			error_handling("logout\nexit: too many arguments", 1);
			return (1);
		}
	}
	get_exit_code(comm_seq);
	return (1);
}
