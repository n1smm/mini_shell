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

#include "libft/libft.h"
#include "minishell.h"

static char	*comm_checker(char *command, char **full_path, bool *success)
{
	int		i;
	char	*path;

	i = 0;
	while (full_path[i])
	{
		path = ft_strjoin(full_path[i++], command); //free??
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

char	*absolute_path(char *command)
{
	if (access(command, X_OK) == 0)
		return (command);
	return (NULL);
}

/* if path is correct it returns allocated, if not it returns NULL */
char *path_finder(char *command, t_shell *data)
{
	char	*env_path;
	char	*path;
	char	**full_path;
	bool	success;

	// if (!command || command == NULL)
	// 	return (NULL);
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


bool correct_path(char *command, t_shell *data)
{
	char	*env_path;
	char	*path;
	char	**full_path;
	bool	success;

	// if (!command || command == NULL)
	// 	return (NULL);
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

/* if the type of token is correct it will allocate, otherwise it returns null not allocated */
/* char	*expander(char *input, t_type typ_token) */
/* { */
/* 	char *result; */
/* 	char *result_path; */

/* 	if (typ_token == COMMAND) */
/* 	{ */
/* 		result = path_finder(input); */
/* 		if (!result) */
/* 			return (NULL); */
/* 		return (result); */


/* 	} */
/* 	else if (typ_token == EXPAND) */
/* 	{ */
/* 		result = getenv(input); */
/* 		result_path = ft_strdup(result); */
/* 		return (result_path); */
/* 	} */
/* 	return (NULL); */
/* } */

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


/* int main(int argc, char **argv) */
/* { */
/* 	if (argc > 3) */
/* 		return 0; */
/* 	char *input; */
/* 	char *input2; */

/* 	input = expander(argv[1], COMMAND); */
/* 	input2 = expander(argv[2], EXPAND); */
/* 	if (!input || !input2) */
/* 	{ */
/* 		printf("not a valid input"); */
/* 		return 1; */
/* 	} */
/* 	printf("command is: %s\n", input); */
/* 	printf("path is: %s\n", input2); */
/* 	free(input); */
/* 	free(input2); */
/* } */
