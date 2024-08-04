/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:01:08 by thiew             #+#    #+#             */
/*   Updated: 2024/08/03 18:01:13 by tjuvan           ###   ########.fr       */
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

int	safe_dup(int old_fd, int new_fd, int which)
{
	int	error;

	if (which == 1)
		error = dup2(old_fd, new_fd);
	else if (which == 0)
		error = dup(old_fd);
	if (error == -1)
		exit(EXIT_FAILURE);
	return (error);
}
