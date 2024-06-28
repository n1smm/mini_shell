/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:20:02 by tjuvan            #+#    #+#             */
/*   Updated: 2023/11/01 19:10:49 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	count;

	count = 0;
	while (count < n)
	{
		if (((unsigned char *)s)[count] == (unsigned char) c)
			return (((unsigned char *) s) + count);
		count++;
	}
	return (NULL);
}

/*
int	main(void)
{
	const	char	strip[20] = "\nbb";
	const	char	strup[20] = " ";
	const	char	strep[20] = " ";

//	puts(strchr(strip, 's'));
//	puts(ft_strchr(strip, 's'));
//	strchr(strip, 'v');
//	ft_strchr(strip, 'v');

	
	printf("%s\n", (char*)memchr(strip, '\n', 3));
    	printf("%s\n", (char*)memchr(strup, 'f', 3));
    	printf("%s\n", (char*)memchr(strep, 0, 3));

    	printf("%s\n", (char*)ft_memchr(strip, '\n', 3));
    	printf("%s\n", (char*)ft_memchr(strup, 'f', 3));
    	printf("%s\n", (char*)ft_memchr(strep, 0, 3));

}*/	
