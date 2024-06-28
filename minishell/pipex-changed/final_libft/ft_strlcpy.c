/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:22:18 by tjuvan            #+#    #+#             */
/*   Updated: 2023/10/25 12:46:07 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//need to compile with flag -lbsd
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	n;
	size_t	i;

	n = 0;
	i = 0;
	while (src[i])
		i++;
	if (size == 0)
		;
	else
	{
		while (n < size - 1 && src[n])
		{
			dst[n] = src[n];
			n++;
		}
		dst[n] = 0;
	}
	return (i);
}
/*
int	main(void)
{
	char	string[20] = "chuchchimuchi";
	char	strung[20] = "mehi";
	char	streng[20] = "hehi";

	int	pip = ft_strlcpy(strung, string, 0);
	puts(strung);
	strlcpy(streng, string, 0);
	puts(streng);
	printf("%i\n", pip);
}*/
