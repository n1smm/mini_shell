/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:44:56 by tjuvan            #+#    #+#             */
/*   Updated: 2023/10/25 15:07:20 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
		return (0);
	while ((s1[count] || s2[count]) && count < n - 1)
	{
		if (s1[count] > s2[count] || s1[count] < s2[count])
			break ;
		count++;
	}
	return ((unsigned char) s1[count] - (unsigned char) s2[count]);
}
/*
int	main(void)
{
	const char	arr1[11] = "test\200";
	const char	arr2[11] = "test\0";

	int work = ft_strncmp(arr1, arr2, 6);
	int werk = strncmp(arr1, arr2, 6);

	printf("%i\n", work);
	printf("%i\n", werk);
}*/
