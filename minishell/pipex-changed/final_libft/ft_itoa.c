/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:38:30 by tjuvan            #+#    #+#             */
/*   Updated: 2023/11/02 18:20:18 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_counter(int n)
{
	int	count;

	n = (long) n;
	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n / 10)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*if_zero(int n)
{
	char	*num;

	num = malloc(2);
	if (!num)
		return (NULL);
	if (n == 0)
	{
		num[0] = '0';
		num[1] = 0;
	}
	return (num);
}

static char	*num_alloc(int size, int n)
{
	char	*number;

	number = malloc((size + 2) * sizeof(char));
	if (!number)
		return (NULL);
	return (number);
}

static char	*calculate(char *num, long numb, int count, int negative)
{
	while (count > negative - 1)
	{
		num[count--] = (numb % 10) + 48;
		numb = numb / 10;
	}
	return (num);
}

char	*ft_itoa(int n)
{
	char	*num;
	long	numb;
	int		negative;
	int		count;

	negative = 0;
	numb = n;
	count = num_counter(n);
	if (numb == 0)
		return (if_zero(n));
	num = num_alloc(count, numb);
	if (!num)
		return (NULL);
	if (numb < 0)
	{
		numb = -numb;
		negative = 1;
		num[0] = '-';
	}
	num = calculate(num, numb, count, negative);
	num[num_counter(n) + 1] = 0;
	return (num);
}
/*
int	main(void)
{
	char	*digs = ft_itoa(1000034);
	if (digs[7] == 0)
		printf("NULL\n");
	printf("%i\n", num_counter(1000034));
	for (int i = 0; i < 4; i++)
		printf("%c\n", digs[i]);
	printf("%s\n", digs);
	free(digs);

}*/
