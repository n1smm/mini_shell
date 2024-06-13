/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:33:57 by tjuvan            #+#    #+#             */
/*   Updated: 2023/10/20 13:30:29 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c > 96 && c < 123)
		c = c - 32;
	return (c);
}
/*
int	main(void)
{
	printf("%c\n",ft_toupper('a'));
	printf("%c\n",ft_toupper('G'));
	printf("%c\n",ft_toupper(121));

	printf("%c\n",toupper('a'));
	printf("%c\n",toupper('G'));
	printf("%c\n",toupper(121));


}*/
