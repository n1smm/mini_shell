/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:09:15 by tjuvan            #+#    #+#             */
/*   Updated: 2023/10/26 18:34:28 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dezt;
	unsigned char	*srz;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	dezt = (unsigned char *) dest;
	srz = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		dezt[i] = srz[i];
		i++;
	}
	return (dest);
}
/* 
int	main(void)
{
	char	done[20] = "";
	char	dons[20] = "";
	char	dins[20] = "";

	puts(done);
	puts(dons);
	ft_memcpy(done, done, 4);
	puts(done);
	memcpy(dons, done, 4);
	puts(dons);
	ft_memcpy(dins, dons, 8);
	for (int i = 0; i < 8; i++)
		printf("%c\t", dins[i]);
}
 */