/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:52:40 by tjuvan            #+#    #+#             */
/*   Updated: 2023/10/20 13:56:39 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
void to_uppercase_even(unsigned int index, char *c)
{
    if (index % 2 == 0 && *c >= 'a' && *c <= 'z')
        *c = *c - 32;
}*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	count;

	count = 0;
	while (s[count])
	{
		f(count, &s[count]);
		count++;
	}
	s[ft_strlen((char *) s)] = 0;
}
/*
int	main(void)
{
	char	arr1[] = "a\tA\t123fishfush";

	ft_striteri(arr1, to_uppercase_even);
	puts(arr1);
}*/
