/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:57:13 by tjuvan            #+#    #+#             */
/*   Updated: 2023/10/24 14:03:23 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		count;
	long	result;
	int		sign;

	count = 0;
	result = 0;
	sign = 0;
	while ((nptr[count] > 8 && nptr[count] < 14) || nptr[count] == 32)
		count++;
	if (nptr[count] == '+')
		count++;
	else if (nptr[count] == '-')
	{
		sign = 1;
		count++;
	}
	while (nptr[count] > 47 && nptr[count] < 58)
	{
		result = (result * 10 + nptr[count]) - 48;
		count++;
	}
	if (sign == 1)
		result = -result;
	return (result);
}
/*
int	main(void)
{
	char *arr1 = "\n \v \t -2147483648";

	printf("%i\n", ft_atoi(arr1));
	printf("%i\n", atoi(arr1));
}*/
