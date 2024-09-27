/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:07:47 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/09/27 16:17:16 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	size_list(t_env_var *tail)
{
	int	i;

	i = 0;
	while (tail)
	{
		tail = tail->next;
		i++;
	}
	return (i);
}

void	ft_env(t_shell *var)
{
	int	i;

	i = 0;
	while (var->env[i])
	{
		printf("%s\n", var->env[i]);
		i++;
	}
}
