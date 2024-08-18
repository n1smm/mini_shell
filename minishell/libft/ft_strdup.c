/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:36:22 by pgiorgi           #+#    #+#             */
/*   Updated: 2023/10/12 17:10:25 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*duplicate;
	int		size;

	size = ft_strlen(s);
	duplicate = malloc((size + 1) * sizeof(char));
	if (!duplicate)
		return (0);
	ft_memcpy(duplicate, s, size);
	duplicate[size] = 0;
	return (duplicate);
}
