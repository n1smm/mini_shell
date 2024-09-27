/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:37:00 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/09/27 15:40:28 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	unset_var_exp_iter_2(t_shell *var, int *j, int *i)
{
	var->exp[*j] = var->exp[*i];
	if ((*i) != (*j))
		var->exp[*i] = NULL;
	(*j)++;
}

static void	unset_var_exp_iter(t_shell *var, int *k, int *i)
{
	*k = *i;
	while (var->exp[(*k) + 1])
	{
		var->exp[*k] = var->exp[(*k) + 1];
		(*k)++;
	}
	var->exp[*k] = NULL;
}

void	unset_var_exp(const char *unset_var, t_shell *var)
{
	int		i;
	int		j;
	size_t	len_value;
	int		k;

	if (!unset_var || !var || !var->env)
		return ;
	i = 0;
	j = 0;
	k = 0;
	while (var->exp[i])
	{
		len_value = ft_strlen(unset_var);
		if (ft_strncmp(var->exp[i], unset_var, len_value) == 0 \
			&& unset_var[len_value] == '\0')
		{
			unset_var_exp_iter(var, &k, &i);
		}
		else
			unset_var_exp_iter_2(var, &j, &i);
		i++;
	}
}
