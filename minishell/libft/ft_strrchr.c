/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:40:13 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/05/19 15:35:04 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*t;

	t = 0;
	if (*s)
	{
		while (*s != '\0')
		{
			if (*s == (unsigned char)c)
			{
				t = s;
			}
			s++;
		}
	}
	if (*s == (unsigned char)c)
	{
		return ((char *)s);
	}
	return ((char *)t);
}
