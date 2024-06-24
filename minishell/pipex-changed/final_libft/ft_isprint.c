/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:22:35 by tjuvan            #+#    #+#             */
/*   Updated: 2023/10/20 13:37:04 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c > 31 && c < 127)
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	printf("%i\n", ft_isprint('3'));
	printf("%i\n", ft_isprint('\n'));
	printf("%i\n", ft_isprint(' '));
	printf("%i\n", ft_isprint(555));
}*/
