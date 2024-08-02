/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:01:08 by thiew             #+#    #+#             */
/*   Updated: 2024/08/02 11:42:38 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void *safe_malloc(size_t size)
{
	void *ptr = malloc(size);
	if (!ptr)
	{
		perror("Malloc failed");
		exit (EXIT_FAILURE);
	}
	return (ptr);
}

char *join_wrapper(const char *s1, const char *s2, int free_which)
{
	char	*result;

	result = ft_strjoin(s1, s2);

	if (free_which == 1)
		free((char *)s1);
	else if (free_which == 2)
		free((char *)s2);
	else if (free_which == 3)
	{
		free((char *)s1);
		free((char *)s2);
	}
	return (result);
}

char	*create_empty_string(int len)
{
	char	*empty;

	empty = safe_malloc(len);
	ft_bzero(empty, len);
	return (empty);
}

int	is_delimiting_node(t_token *curr)
{
	if (curr->typ_token == WHITESPACE)
		return (1);
	if (curr->typ_token == PIPELINE)
		return (1);
	if (curr->typ_token == REDIRECT_IN)
		return (1);
	if (curr->typ_token == REDIRECT_OUT)
		return (1);
	if (curr->typ_token == REDIRECT_IN_DOUBLE)
		return (1);
	if (curr->typ_token == REDIRECT_OUT_DOUBLE)
		return (1);
	else
		return(0);
}

int	is_delimiting_type(t_type type)
{
	if (type == WHITESPACE)
		return (1);
	if (type == PIPELINE)
		return (1);
	if (type == REDIRECT_IN)
		return (1);
	if (type == REDIRECT_OUT)
		return (1);
	if (type == REDIRECT_IN_DOUBLE)
		return (1);
	if (type == REDIRECT_OUT_DOUBLE)
		return (1);
	else
		return(0);
}
