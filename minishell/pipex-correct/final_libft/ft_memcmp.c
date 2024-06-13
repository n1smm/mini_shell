/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:44:56 by tjuvan            #+#    #+#             */
/*   Updated: 2023/10/25 15:12:35 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		count;
	const char	*str1;
	const char	*str2;

	count = 0;
	str1 = (const char *) s1;
	str2 = (const char *) s2;
	if (n <= 0)
		return (0);
	while (count < n - 1)
	{
		if (str1[count] > str2[count] || str1[count] < str2[count])
			break ;
		count++;
	}
	return ((unsigned char) str1[count] - (unsigned char) str2[count]);
}
/*
int	main(void)
{
	const char	arr1[11] = "1234567890";
	const char	arr2[11] = "1234567890";

	int work = ft_memcmp(arr1, arr2, 15);
	int werk = memcmp(arr1, arr2, 15);

	printf("%i\n", work);
	printf("%i\n", werk);

}*/
