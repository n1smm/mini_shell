/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:58:41 by tjuvan            #+#    #+#             */
/*   Updated: 2023/11/01 18:09:05 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen2(const char *l)
{
	size_t	i;

	i = 0;
	while (l[i])
		i++;
	return (i);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	b_count;
	size_t	l_count;
	size_t	size_little;

	b_count = 0;
	l_count = 0;
	size_little = ft_strlen2(little);
	if (size_little == 0)
		return ((char *)big);
	while (big[b_count] && b_count < len)
	{
		while (big[b_count] == little[l_count] && b_count < len)
		{
			if (l_count + 1 == size_little)
				return ((char *)(big + b_count - l_count));
			b_count++;
			l_count++;
		}
		if (l_count != 0)
			b_count = b_count - l_count;
		l_count = 0;
		b_count++;
	}
	return (0);
}
/*
int	main(void)
{
	char	bigger[27] = "aaabcabcd";
	char	smaller[20] = "aabc";

	printf("%s\n", ft_strnstr(bigger, smaller, 5));
	printf("%s\n", strnstr(bigger, smaller, 5));
	printf("%i\n", ft_strlen2(smaller));
}*/
