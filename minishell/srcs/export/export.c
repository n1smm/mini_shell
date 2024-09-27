/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:50:11 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/09/27 16:47:27 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	printf_export(t_shell *var)
{
	int	i;

	i = 0;
	while (var->exp[i])
	{
		printf("declare -x: %s\n", var->exp[i]);
		i++;
	}
}

static void	exporting(t_shell *var, char *arg, int *flag)
{
	if (valid_env_var(arg) == 0)
	{
		*flag = 1;
		add_to_env(var, arg);
		add_to_export(var, arg);
	}
	else if (valid_env_var(arg) == 1)
	{
		*flag = 1;
		printf("export: `%s': not a valid identifier\n", arg);
	}
	else
	{
		*flag = 1;
		add_to_export2(var, arg);
	}
}

void	ft_export(t_shell *var, char **args)
{
	int		i;
	int		index_var;
	int		flag;

	i = 0;
	index_var = 0;
	flag = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "export\0", 7) == 0)
			index_var = i + 1;
		i++;
	}
	while (args[index_var] && args[index_var][0] != '|')
	{
		exporting(var, args[index_var], &flag);
		index_var++;
	}
	if (flag == 0)
		printf_export(var);
	return ;
}
