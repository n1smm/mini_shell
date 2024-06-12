/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:07:47 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/06/12 17:39:16 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	env(void)
{
	char	env[1024];

	if (getenv(env) != NULL)
	{
		printf("env: %s\n", env);
		return (true);
	}
	else
	{
		printf("env error\n");
		return (false);
	}
}