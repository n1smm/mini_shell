/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:43:57 by tjuvan            #+#    #+#             */
/*   Updated: 2023/11/01 19:26:12 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	len_s;

	len_s = ft_strlen((char *) s);
	if (start > len_s)
	{
		substring = malloc(1);
		if (!substring)
			return (NULL);
		substring[0] = 0;
		return (substring);
	}
	if (start + len > len_s)
		len = len_s - start;
	substring = malloc((len + 1) * sizeof(char));
	if (!substring)
		return (0);
	ft_strlcpy(substring, s + start, len + 1);
	return (substring);
}
/*
int	main(void)
{
	char	*dest;
	char	*src = "give me money";
	
	dest = ft_substr(src, 2, 2);
	puts(dest);
	free(dest);
}
*/
