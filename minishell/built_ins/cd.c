/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:07:41 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/09/25 16:24:24 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_cd(const char *path, char **input)
{
	int i;

	i = 0;
	if (!path)
		return (-1);
	while(input[i])
		i++;
	if (i > 2)
	{
		g_error_code = 1;
		printf("-bash: cd: too many arguments");
		return (true);
	}
	if (chdir(path) == -1)
	{
		g_error_code = 1;
		printf("-bash: cd: %s: No such file or directory", path);
	}
	else
		chdir(path);
	return(true);
}
