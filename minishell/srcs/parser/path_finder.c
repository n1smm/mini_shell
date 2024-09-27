/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:51:02 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/09/27 16:19:20 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*comm_checker(char *command, char **full_path, bool *success)
{
	int		i;
	char	*path;

	i = 0;
	while (full_path[i])
	{
		path = ft_strjoin(full_path[i++], command);
		if (0 == access(path, X_OK))
		{
			*success = true;
			break ;
		}
		free(path);
	}
	if (*success == false)
		return (NULL);
	return (path);
}

char	*absolute_path(char *command)
{
	if (access(command, X_OK) == 0)
		return (command);
	return (NULL);
}

char	*path_finder(char *command, t_shell *data)
{
	char	*env_path;
	char	*path;
	char	**full_path;
	bool	success;

	env_path = custom_getenv("PATH", data->env);
	success = false;
	if (!command)
		return (NULL);
	if (ft_strchr(command, '/'))
		return (absolute_path(command));
	full_path = ft_split(env_path, ':');
	command = ft_strjoin("/", command);
	path = comm_checker(command, full_path, &success);
	free(command);
	free_mtx((void **)full_path);
	if (success == true)
		return (path);
	return (NULL);
}

bool	correct_path(char *command, t_shell *data)
{
	char	*env_path;
	char	*path;
	char	**full_path;
	bool	success;

	env_path = custom_getenv("PATH", data->env);
	success = false;
	if (!command)
		return (NULL);
	if (ft_strchr(command, '/'))
		return (absolute_path(command));
	full_path = ft_split(env_path, ':');
	command = ft_strjoin("/", command);
	path = comm_checker(command, full_path, &success);
	free(command);
	free_mtx((void **)full_path);
	free(path);
	if (success == true)
		return (true);
	return (false);
}
