/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:33:57 by tjuvan            #+#    #+#             */
/*   Updated: 2023/10/20 13:37:23 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (c);
	else
		return (0);
}
/*
int	main(void)
{
	printf("%i\n",ft_isalpha('a'));
	printf("%i\n",ft_isalpha('G'));
	printf("%i\n",ft_isalpha('0'));

}*/
