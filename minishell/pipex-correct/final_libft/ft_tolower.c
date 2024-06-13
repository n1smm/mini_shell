/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:33:57 by tjuvan            #+#    #+#             */
/*   Updated: 2023/10/20 13:31:05 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c > 64 && c < 91)
		c = c + 32;
	return (c);
}
/*
int	main(void)
{
	printf("%c\n",ft_tolower('A'));
	printf("%c\n",ft_tolower('Z'));
	printf("%c\n",ft_tolower(121));

	printf("%c\n",tolower('A'));
	printf("%c\n",tolower('Z'));
	printf("%c\n",tolower(121));


}*/
