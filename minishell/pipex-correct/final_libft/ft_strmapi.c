/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:38:48 by tjuvan            #+#    #+#             */
/*   Updated: 2023/10/20 13:55:58 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
char to_uppercase(unsigned int index, char c) {
    if (c >= 'a' && c <= 'z')
        return c - 32;
    return c;
}*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	count;
	char			*arr;

	count = 0;
	arr = malloc(ft_strlen((char *) s) * sizeof(char) + 1);
	if (!arr)
		return (NULL);
	while (s[count])
	{
		arr[count] = f(count, s[count]);
		count++;
	}
	arr[ft_strlen((char *) s)] = 0;
	return (arr);
}
/*
int	main(void)
{
	char	*arr;
	char	*arr1 = "a\tA\t123";

	arr = ft_strmapi(arr1, to_uppercase);
	puts(arr);
	free(arr);
}*/
