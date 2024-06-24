/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:29:24 by tjuvan            #+#    #+#             */
/*   Updated: 2023/11/01 19:11:45 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*al_space;

	al_space = malloc(nmemb * size);
	if (!al_space)
		return (NULL);
	ft_bzero(al_space, nmemb * size);
	return (al_space);
}
/* 
int	main(void)
{
	char	*arr1;
	char	*arr2;
	int	size;

	size = 8539;

	arr1 = ft_calloc(size, sizeof(int));
	arr2 = calloc(size, sizeof(int));

	for (int i = 0; i < size; i++)
		printf("%d\t", arr2[i]);
	printf("\n\n\n\n");

	for (int i = 0; i < size; i++)
		printf("%d\t", arr1[i]);
	free(arr1);
	free(arr2);
}*/
