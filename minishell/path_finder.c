/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:29:52 by thiew             #+#    #+#             */
/*  Updated: 2024/05/19 16:43:26 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static char	*comm_checker(char *command, char **full_path, bool *success)
{
	int		i;
	char	*path;

	i = 0;
	while (full_path[i])
	{
		path = ft_strjoin(full_path[i++], command);
		if ( 0 == access(path, X_OK))
		{
			*success = true;
			break ;
		}
		free(path);
	}
	if (*success == false)
		return (NULL);
	return(path);

}

char *path_finder(char *command)
{
	char	*env_path;
	char	*path;
	char	**full_path;
	bool	success;
	
	env_path = getenv("PATH");
	success = false;
	if (!command)
		return (NULL);
	full_path = ft_split(env_path, ':');
	command = ft_strjoin("/", command);
	path = comm_checker(command, full_path, &success);
	free(command);
	free_mtx((void **)full_path);
	if (success == true)
		return (path);
	return (NULL);
}

/* int	main(int argc, char **argv) */
/* { */
/* 	if (argc > 2) */
/* 		return 0; */

/* 	char *result; */

/* 	result = path_finder(argv[1]); */
/* 	if (result) */
/* 	{ */
/* 		puts(result); */
/* 		free(result); */
/* 	} */
/* 	return 0; */
/* } */
