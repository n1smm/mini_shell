/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:53:14 by tjuvan            #+#    #+#             */
/*   Updated: 2023/11/01 19:07:59 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dezt;
	unsigned char	*srz;
	size_t			i;

	dezt = (unsigned char *) dest;
	srz = (unsigned char *) src;
	i = 0;
	if (!dezt && !srz)
		return (NULL);
	if (dezt > srz)
	{
		while (n > 0)
		{
			dezt[n - 1] = srz[n - 1];
			n--;
		}
	}
	while (i < n)
	{
		dezt[i] = srz[i];
		i++;
	}
	return (dezt);
}
/* 
int	main(void)
{
	char	pip[20] = "";
	char	pup[20] = "";

	ft_memmove(0, pip, 0);
	puts(pip);
	memmove(0, pup, 0);
	puts(pup);
	memcpy(pip, pip + 4, 2);
	puts(pip);
} */
