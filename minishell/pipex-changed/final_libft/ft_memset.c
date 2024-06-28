/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:44:50 by tjuvan            #+#    #+#             */
/*   Updated: 2023/10/20 13:36:26 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *) s;
	while (i < n)
	{
		ptr[i++] = (unsigned char) c;
	}
	return (s);
}
/*
int	main(void)
{
	char	strunz[20] = "leavehere";
	char	strunzo[20] = "leavehere";
	
	ft_memset(strunz + 3, 48, 3);
	puts(strunz);
	memset(strunzo + 3, 48, 3);
	puts(strunzo);
}
*/
