/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:33:37 by tjuvan            #+#    #+#             */
/*   Updated: 2023/11/02 13:35:39 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	count;

	count = 0;
	if (!s)
		return ((void) NULL);
	while (s[count])
		write(fd, &s[count++], 1);
	write(fd, "\n", 1);
}
/*
int	main(void)
{
	ft_putendl_ft("no where like home", 1);
}*/
