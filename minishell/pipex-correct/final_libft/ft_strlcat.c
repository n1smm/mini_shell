/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:22:18 by tjuvan            #+#    #+#             */
/*   Updated: 2023/10/25 14:37:02 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//need to compile with flag -lbsd
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	count_after;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	count_after = 0;
	if (!dst && size == 0)
		return (src_len);
	if (size <= dst_len)
		return (src_len + size);
	else
	{
		while (count_after < size - dst_len - 1 && src[count_after])
		{
			dst[count_after + dst_len] = src[count_after];
			count_after++;
		}
		dst[count_after + dst_len] = 0;
	}
	return (dst_len + src_len);
}

/*
int	main(void)
{
	//char	string[20] = "0123456789";
	char	strung[15];
	char	streng[15];
	strung[10] = 'a';
	streng[10] = 'a';

	int	pip = ft_strlcat(strung, "lorem ipsum dolor sit amet", 6);
	puts(strung);
	int	pup = strlcat(streng, "lorem ipsum dolor sit amet", 6);
	puts(streng);
	printf("%i\n", pip);
	printf("%i\n", pup);
}*/
