/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:15:08 by thiew             #+#    #+#             */
/*   Updated: 2024/09/27 15:04:05 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	check_n_flag(char *input)
{
	int	i;

	i = 0;
	if (ft_strncmp(input, "-n", 2) == 0)
	{
		i += 2;
		if (input[i] == 'n')
		{
			while (input[i] == 'n')
				i++;
		}
		if (input[i] == 0)
			return (0);
		else
			return (1);
	}
	else
		return (1);
}

void	ft_echo(char **args)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (args[i] == NULL)
	{
		printf("\n");
		return ;
	}
	while (args[i] && check_n_flag(args[i]) == 0)
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (n_flag == 0)
		printf("\n");
}
