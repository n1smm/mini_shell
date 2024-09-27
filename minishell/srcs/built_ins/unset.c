/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:07:50 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/09/27 18:52:43 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	unset_var_iter_2(t_shell *var, int *j, int *i)
{
	var->env[*j] = var->env[*i];
	if ((*i) != (*j))
		var->env[*i] = NULL;
	(*j)++;
}

static void	unset_var_iter(t_shell *var, int *k, int *i)
{
	*k = *i;
	while (var->env[(*k) + 1])
	{
		var->env[*k] = var->env[(*k) + 1];
		(*k)++;
	}
	var->env[*k] = NULL;
}

void	unset_var(const char *uns, t_shell *var)
{
	int		i;
	int		j;
	char	*eq;
	size_t	l_val;
	int		k;

	if (!uns || !var || !var->env)
		return ;
	i = 0;
	j = 0;
	k = 0;
	while (var->env[i])
	{
		eq = ft_strchr(var->env[i], '=');
		if (eq)
		{
			l_val = eq - var->env[i];
			if (ft_strncmp(var->env[i], uns, l_val) == 0 && uns[l_val] == '\0')
				unset_var_iter(var, &k, &i);
			else
				unset_var_iter_2(var, &j, &i);
		}
		i++;
	}
}

int	ft_unset(t_shell *var, char **args)
{
	int		i;
	int		index_var;

	i = 0;
	index_var = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "unset\0", 6) == 0)
			index_var = i + 1;
		i++;
	}
	while (args[index_var] && args[index_var][0] != '|')
	{
		unset_var(args[index_var], var);
		unset_var_exp(args[index_var], var);
		index_var++;
	}
	return (1);
}
