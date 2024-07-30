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

// void    unset_var2(char **unset_var, t_shell *var, )
// {
    
// }

void    unset_var(char **unset_var, t_shell *var)
{
    int i;
    int j;
    int z;
    int x;
    int index_uv;

    x = 0;
    i = 0;
    j = 0;
    z = 0;
    while(unset_var[x] && unset_var[x][0] != '|')
    {
        i = 0;
        z = 0;
        j = 0;
        index_uv = 0;
        while(var->env[i])
        {
            j = 0;
            while(var->env[i][j] != '=')
                j++;
            if (var->env[i][j] == '=')
                index_uv = j;
            if(ft_strncmp(var->env[i], unset_var[x], index_uv) == 0)
                i++;
            var->env[z] = ft_strdup(var->env[i]);
            i++;
            z++;
        }
        x++;
    }
    var->env[z + 1] = NULL;
    return ;

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
    // args[i + 1] = '\0';
    unset_var(args + index_var, var);
    return ;

}