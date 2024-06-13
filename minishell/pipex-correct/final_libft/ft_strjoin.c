/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:21:34 by tjuvan            #+#    #+#             */
/*   Updated: 2024/04/08 19:21:42 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2, int free_all)
{
	size_t	count_later;
	size_t	count;
	char	*twin;

	count = 0;
	count_later = count;
	twin = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!twin || !s1 || !s2)
	{
		free(s1);
		return (NULL);
	}
	while (s1[count])
	{
		twin[count] = s1[count];
		count++;
	}
	while (s2[count_later])
		twin[count++] = s2[count_later++];
	twin[count] = 0;
	if (free_all == 1 && free_all != 2)
		free(s2);
	if (free_all != 2)
		free(s1);
	return (twin);
}
