/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:15:08 by thiew             #+#    #+#             */
/*   Updated: 2024/06/24 12:18:20 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char *str)
{
	int	i;

	i = 0;
	if(!str)
	{
		printf("\n");
		return ;
	}
	while (str[i])
	{
		printf("%c", str[i]);
		i++;
	}
	printf("\n");
}
/* int	main(int argc, char **argv) */
/* { */
/* 	int		i; */
/* 	char 	*token; */
	
/* 	if (argc <1) */
/* 		return 0; */


	
/* 	return 0; */
/* } */
