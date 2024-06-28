/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:50:13 by tjuvan            #+#    #+#             */
/*   Updated: 2023/10/20 13:37:40 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *) s;
	while (i < n)
		ptr[i++] = 0;
}
/*
int	main(void)
{
	char	fifi[20] = "miii5";
	char	fifo[20] = "miii5";
	puts(fifi);	
	ft_bzero(fifi + 3, 1);
	puts(fifi);
	bzero(fifo + 3, 1);
	puts(fifo);
}*/
