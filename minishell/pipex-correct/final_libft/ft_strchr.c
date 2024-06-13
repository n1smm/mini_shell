/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:24:21 by tjuvan            #+#    #+#             */
/*   Updated: 2023/11/01 17:17:34 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		count;
	char	*src;
	char	lulek;

	lulek = (char) c;
	count = 0;
	src = (char *)s;
	count = 0;
	while (src[count] != lulek)
	{
		if (src[count] == 0)
			return (0);
		count++;
	}
	return (src + count);
}

/*
int	main(void)
{
	const	char	strip[20] = "teste";
	const	char	strup[20] = "";
	const	char	strep[20] = "";

//	puts(strchr(strip, 's'));
//	puts(ft_strchr(strip, 's'));
//	strchr(strip, 'v');
//	ft_strchr(strip, 'v');


	printf("%s\n", strchr(0x564b3575f0a6: "teste", 357: 'e'));
	printf("%s\n", strchr(strup, 'f'));
	printf("%s\n", strchr(strep, '\0'));

	printf("%s\n", ft_strchr(0x564b3575f0a6: "teste", 357: 'e'));
	printf("%s\n", ft_strchr(strup, 'f'));
	printf("%s\n", ft_strchr(strep, '\0'));

}*/
