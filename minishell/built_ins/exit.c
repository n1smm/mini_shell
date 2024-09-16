/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 22:21:25 by thiew             #+#    #+#             */
/*   Updated: 2024/09/03 13:18:12 by thiew            ###   ########.fr       */
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
	if (is_number(comm_seq[1]))
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

int	ft_exit(t_shell *data, char **comm_seq, t_token **tail, t_token **head)
{
	*data=*data;	
	write(STDERR_FILENO, "exit", 4);
	write(STDERR_FILENO, "\n", 1);
	if (tail)
	{
		free_tokens_final(tail, head);
		/* free_garbage(t_token *garbage); */
	}
	if (comm_seq[1] && comm_seq[2])
	{
		write(STDERR_FILENO, "too many arguments", 18);
		return (EXIT_FAILURE);
	}
	//free eveerything
	get_exit_code(comm_seq);
	return (1);
}
