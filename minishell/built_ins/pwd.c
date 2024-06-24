/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:12:04 by thiew             #+#    #+#             */
/*   Updated: 2024/06/24 11:09:28 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_pwd(void)
{
	char	pwd[1024];

	if (getcwd(pwd, 1024) != NULL)
	{
		printf("%s\n", pwd);
		return (true);
	}
	else
	{
		printf("pwd error\n");
		return (false);
	}
}
