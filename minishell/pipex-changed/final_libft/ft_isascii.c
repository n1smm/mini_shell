/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:22:35 by tjuvan            #+#    #+#             */
/*   Updated: 2023/10/20 13:37:15 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c < 128)
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	printf("%i\n", ft_isascii(3));
	printf("%i\n", ft_isascii('\n'));
	printf("%i\n", ft_isascii(' '));
	printf("%i\n", ft_isascii(555));
}*/
