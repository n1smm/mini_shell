/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:33:31 by tjuvan            #+#    #+#             */
/*   Updated: 2023/10/25 19:05:35 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*one_byte_str(void)
{
	char	*one_byte;

	one_byte = malloc(sizeof(char));
	if (!one_byte)
		return (0);
	one_byte[0] = 0;
	return (one_byte);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	trim_len;
	char	*trimmed;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, (int) s1[start]))
		start++;
	while (s1[end] >= 0 && ft_strchr(set, (int) s1[end]))
		end--;
	if (start == ft_strlen(s1))
		return (one_byte_str());
	if (end != ft_strlen(s1))
		trim_len = ft_strlen(s1) - start - (ft_strlen(s1) - end) + 1;
	else
		trim_len = ft_strlen(s1) - start;
	trimmed = malloc((trim_len + 1) * sizeof(char));
	if (!trimmed)
		return (0);
	ft_strlcpy(trimmed, s1 + start, trim_len + 1);
	trimmed[ft_strlen(trimmed)] = 0;
	return (trimmed);
}
/*
int	main(void)
{
	char	*to_trim = "lorem \n ipsum \t dolor \n sit \t amet";
	char	*trimmer = " ";
	char	*result;

	result = ft_strtrim(to_trim, trimmer);
	puts(result);
	free(result);
}*/