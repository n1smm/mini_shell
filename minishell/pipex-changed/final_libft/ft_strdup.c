/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:14:58 by tjuvan            #+#    #+#             */
/*   Updated: 2023/10/25 15:34:26 by tjuvan           ###   ########.fr       */
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
/*
int	main(void)
{
	char	*arr1 = "duplichate";
	char	*arr2;
	
	arr2 = ft_strdup(arr1);
	puts(arr2);
	free(arr2);
	
	char	*arr3 = "duplichate";
	char	*arr4;
	
	arr4 = strdup(arr3);
	puts(arr4);
	free(arr4);

}*/
