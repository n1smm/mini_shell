/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:49:24 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/09/27 16:20:33 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strdup2(const char *s, size_t end)
{
	char	*i;
	size_t	j;
	size_t	z;

	j = 0;
	z = 0;
	while (s[z])
	{
		z++;
	}
	i = (char *) malloc(sizeof(char) * z + 1);
	if (!i)
		return (NULL);
	while (j < (end))
	{
		i[j] = s[j];
		j++;
	}
	i[j] = '\0';
	return ((char *)i);
}

void	ft_add_token(const char *word, size_t end, t_type type, t_token **head)
{
	char	*str;

	if (!word || !head || !*head)
		return ;
	str = ft_strdup2(word, end);
	if (!str)
		return ;
	double_lstadd_back(str, head);
	(*head)->typ_token = type;
}

char	*ft_chardup(char character)
{
	char	*i;

	if (!character)
		return (NULL);
	i = (char *)safe_malloc(sizeof(char) * 2);
	i[0] = character;
	i[1] = '\0';
	return ((char *)i);
}

bool	term_character(char c)
{
	if (c == ' ' || c == '\t' || c == '|' || c == '<' \
		|| c == '>' || c == 0 || c == '\"' || c == '\'')
	{
		return (true);
	}
	else
		return (false);
}
