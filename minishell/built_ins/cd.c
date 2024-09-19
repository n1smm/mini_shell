/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:07:41 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/06/24 11:08:49 by pgiorgi          ###   ########.fr       */
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
		printf("-bash: cd: too many arguments");
		return (true);
	}
	if (chdir(path) == -1)
	{
		printf("-bash: cd: %s: No such file or directory", path);
	}
	else
		chdir(path);
	return(true);
}
