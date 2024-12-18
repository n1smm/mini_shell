/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:01:08 by thiew             #+#    #+#             */
/*   Updated: 2024/09/27 16:42:42 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*safe_malloc(size_t size)
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

char	*join_wrapper(const char *s1, const char *s2, int free_which)
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

	error = 0;
	if (which == 1)
		error = dup2(old_fd, new_fd);
	else if (which == 0)
		error = dup(old_fd);
	if (error == -1)
	{
		error_handling("Dup2 failed, exiting program", errno);
		exit(EXIT_FAILURE);
	}
	return (error);
}

int	safe_open(char *pathname, int flags, mode_t mode)
{
	int	fd;

	fd = open(pathname, flags, mode);
	if (fd == -1)
		error_handling("problem opening file", errno);
	return (fd);
}
