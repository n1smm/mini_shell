/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:07:41 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/09/27 16:17:08 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	ft_cd(const char *path, char **input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	if (i > 2)
	{
		error_handling("-bash: cd: too many arguments", 1);
		return (true);
	}
	if (!input[1] || ft_strncmp(input[1], "~", 2) == 0)
	{
		chdir(getenv("HOME"));
		return (true);
	}
	if (chdir(path) == -1)
	{
		error_handling("-bash: cd: %s: No such file or directory", 1);
		return (true);
	}
	return (true);
}
