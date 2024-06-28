/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:48:13 by tjuvan            #+#    #+#             */
/*   Updated: 2023/10/20 14:02:17 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	int	alpha;
	int	digit;

	alpha = ft_isalpha(c);
	digit = ft_isdigit(c);
	if (alpha > 0 || digit > 0)
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	printf("%i\n", ft_isalnum('2'));
	printf("%i\n", ft_isalnum('0'));
	printf("%i\n", ft_isalnum(8));
	printf("%i\n", ft_isalnum(')'));
}*/
