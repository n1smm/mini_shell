/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:15:08 by thiew             #+#    #+#             */
/*   Updated: 2024/06/13 17:01:31 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char *str)
{
	long	i;

	i = 0;
	if(!str)
		return ;
	while (str[i])
	{
		printf("%c", str[i]);
		i++;
	}
}
/* int	main(int argc, char **argv) */
/* { */
/* 	int		i; */
/* 	char 	*token; */
	
/* 	if (argc <1) */
/* 		return 0; */


	
/* 	return 0; */
/* } */
