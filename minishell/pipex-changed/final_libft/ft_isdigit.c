/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:33:22 by tjuvan            #+#    #+#             */
/*   Updated: 2023/10/20 13:37:10 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	printf("%i\n", ft_isdigit('0'));
	printf("%i\n", ft_isdigit('9'));
	printf("%i\n", ft_isdigit(3));
}*/
