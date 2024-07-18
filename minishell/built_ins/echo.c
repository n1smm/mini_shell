/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:15:08 by thiew             #+#    #+#             */
/*   Updated: 2024/07/18 19:09:07 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char **args)
{
	int	i;
	int	j;
	int	n_flag;

	i = 1;
	j = 0;
	n_flag = 0;
	printf("TESTING ECHO");
	if(args[1][0])
	{
		while (args[i])
		{
			if (args[i][j] == '-')
			{
				if(args[i][j + 1] == 'n' && (args[i][j + 2] == ' ' \
					|| args[i][j + 2] == '\t'))
					n_flag = 1;
				i++;
			}
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if(args[i + 1] && args[i][0] != '\0')
				printf(" ");
			i++;
		}
	}
	if (n_flag == 0)
		printf("\n");
	return ;
}
/* int	main(int argc, char **argv) */
/* { */
/* 	int		i; */
/* 	char 	*token; */
	
/* 	if (argc <1) */
/* 		return 0; */


	
/* 	return 0; */
/* } */
