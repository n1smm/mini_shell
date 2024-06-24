/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:09:19 by tjuvan            #+#    #+#             */
/*   Updated: 2023/11/07 09:49:34 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_counter(char const *word, char c)
{
	int	count;
	int	word_count;

	count = 0;
	word_count = 0;
	while (word[count] != 0)
	{
		if (word[count] == c)
			count++;
		else
		{
			word_count++;
			while (word[count] && word[count] != c)
				count++;
		}
	}
	return (word_count);
}

static char	*word_placer(char *word, char const *s, int i, int word_len)
{
	int	count;

	count = 0;
	while (word_len > 0)
	{
		word[count] = s[i - word_len];
		count++;
		word_len--;
	}
	word[count] = 0;
	return (word);
}

static char	**free_arr(char **big, int count)
{
	while (count > 0)
	{
		count--;
		free(big[count]);
	}
	free(big);
	return (0);
}

static char	**word_splitter(char const *s, char c, char **s2, int num_words)
{
	int	count;
	int	nbr_word;
	int	word_len;

	count = 0;
	nbr_word = 0;
	word_len = 0;
	while (nbr_word < num_words)
	{
		while (s[count] && s[count] == c)
			count++;
		while (s[count] && s[count] != c)
		{
			count++;
			word_len++;
		}
		s2[nbr_word] = (char *)malloc(sizeof(char) * (word_len + 1));
		if (!s2)
			return (free_arr(s2, nbr_word));
		word_placer(s2[nbr_word], s, count, word_len);
		word_len = 0;
		nbr_word++;
	}
	s2[nbr_word] = 0;
	return (s2);
}

char	**ft_split(char const *s, char c)
{
	char			**s2;
	unsigned int	num_of_words;

	if (!s)
		return (0);
	num_of_words = word_counter(s, c);
	s2 = (char **)malloc(sizeof(char *) * (num_of_words + 1));
	if (!s2)
		return (0);
	s2 = word_splitter(s, c, s2, num_of_words);
	return (s2);
}
