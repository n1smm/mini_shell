/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 09:25:24 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/09/27 16:16:28 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "../minishell.h"

static void	*safe_malloc_libft(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		error_handling("Malloc failed, exiting program", errno);
		exit (EXIT_FAILURE);
	}
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	j;
	size_t	x;
	size_t	y;

	j = ft_strlen(s2);
	x = 0;
	y = 0;
	s3 = (char *)safe_malloc_libft(sizeof(char) * (ft_strlen(s1) + j + 1));
	while (x < ft_strlen(s1))
	{
		s3[y] = s1[y];
		y++;
		x++;
	}
	while (y < (ft_strlen(s1) + j))
	{
		s3[y] = s2[y - ft_strlen(s1)];
		y++;
	}
	s3[y] = '\0';
	return ((char *)s3);
}
