/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:15:08 by thiew             #+#    #+#             */
/*   Updated: 2024/06/12 18:21:38 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char *str)
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
