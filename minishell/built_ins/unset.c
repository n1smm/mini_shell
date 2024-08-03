/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:07:50 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/06/12 17:07:51 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void unset_var(const char *unset_var, t_shell *var)
{
	int		i;
	int		j;
	char	*eq;
	size_t 	len_value;

	if (!unset_var || !var || !var->env)
        return;
    i = 0;
	j = 0;
    while (var->env[i])
    {
        eq = ft_strchr(var->env[i], '=');
        if (eq)
        {
            len_value = eq - var->env[i];
            if (ft_strncmp(var->env[i], unset_var, len_value) == 0 \
				&& unset_var[len_value] == '\0')
            {
                free(var->env[i]);
                int k = i;
                while (var->env[k + 1])
                {
                    var->env[k] = var->env[k + 1];
                    k++;
                }
                var->env[k] = NULL;
            }
            else
            {
                var->env[j] = var->env[i];
                if (i != j)
                    var->env[i] = NULL;
                j++;
            }
        }
        i++;
    }
}

void    ft_unset(t_shell *var, char **args)
{
    int     i;
    int     index_var;
    char **tmp;

    i = 0;

    i = i;
    tmp = NULL;
    tmp = tmp;
    var = var;
    args = args;
    index_var = 0;

    while(args[i])
    {
        if(ft_strncmp(args[i], "unset\0", 6) == 0)
            index_var = i + 1;
        i++;
    }
    while (args[index_var] && args[index_var][0] != '|')
	{
		unset_var(args[index_var], var);
		index_var++;
	}
}
