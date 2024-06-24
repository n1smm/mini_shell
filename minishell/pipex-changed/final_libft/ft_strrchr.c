/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:24:21 by tjuvan            #+#    #+#             */
/*   Updated: 2023/11/01 17:25:48 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		count;
	char	*src;
	char	lul;

	lul = c;
	count = 0;
	src = (char *) s;
	while (src[count])
		count++;
	while (count >= 0)
	{
		if (src[count] == lul)
			return (src + count);
		count--;
	}
	return (0);
}
/* 
int	main(void)
{
	const	char	strip[20] = "bbgregu12345";
	const	char	strup[20] = "holipofi ";
	const	char	strep[20] = "1234567890 ";

//	puts(strchr(strip, 's'));
//	puts(ft_strrchr(strip, 's'));
//	strchr(strip, 'v');
//	ft_strrchr(strip, 'v');

	
	printf("%s\n", strrchr(strip, 'b'));
	printf("%s\n", strrchr(strup, 'f'));
	printf("%s\n", strrchr(strep, 0));
	
	printf("%s\n", ft_strrchr(strip, 'b'));
	printf("%s\n", ft_strrchr(strup, 'f'));
	printf("%s\n", ft_strrchr(strep, 0));

} */
