/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 22:21:25 by thiew             #+#    #+#             */
/*   Updated: 2024/08/28 18:43:55 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	//TODO check also for sign - or + and length of the code
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
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
		//print out the argument
		write(STDERR_FILENO, "numeric argument required", 25);
	}
	g_error_code = exit_code;
	exit(exit_code);
}

int	ft_exit(t_shell *data, char **comm_seq)
{
	*data=*data;	
	write(STDERR_FILENO, "exit", 4);
	if (comm_seq[1] && comm_seq[2])
	{
		write(STDERR_FILENO, "too many arguments", 18);
		return (EXIT_FAILURE);
	}
	//free eveerything
	get_exit_code(comm_seq);
	return (EXIT_SUCCESS);
}
