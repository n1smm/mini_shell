/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:50:35 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/09/27 16:21:12 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	valid_env_var(char *args)
{
	int	j;

	j = 0;
	if (args[j] == '\0')
		return (1);
	if (args[j])
	{
		if (args[j] != '_' && !(ft_isalpha(args[j])))
			return (1);
	}
	while (args[j])
	{
		if (args[j] == '=')
		{
			if (check_env_var(args, j) == 1)
				return (1);
			else
				return (0);
		}
		j++;
	}
	if (!(ft_strchr(args, '=')))
		return (2);
	return (0);
}

static char	*add_to_env_supp_3(t_shell *var, char *new, char **tmp, int i)
{
	new = ft_strjoin(tmp[0], tmp[1]);
	if (new)
	{
		add_to_garbage(&(var)->garbage, new);
		var->env[i] = ft_strdup(new);
		add_to_garbage(&(var)->garbage, var->env[i]);
		var->env[i + 1] = NULL;
		add_to_garbage(&(var)->garbage, var->env[i + 1]);
	}
	return (new);
}

static char	*add_to_env_supp_2(t_shell *var, char *new, char **tmp, int i)
{
	new = join_wrapper(tmp[0], tmp[1], 0);
	if (new)
	{
		add_to_garbage(&(var)->garbage, new);
		var->env[i] = ft_strdup(new);
		add_to_garbage(&(var)->garbage, var->env[i]);
	}
	return (new);
}

static void	add_env_supp(t_shell *var, char **tmp, char *new_var, int i_nv)
{
	add_to_garbage(&(var)->garbage, tmp);
	tmp[0] = ft_substr(new_var, 0, i_nv + 1);
	add_to_garbage(&(var)->garbage, tmp[0]);
	if (!tmp[0])
	{
		free(tmp);
		return ;
	}
	tmp[1] = ft_substr(new_var, i_nv + 1, ft_strlen(new_var));
	add_to_garbage(&(var)->garbage, tmp[1]);
	if (!tmp[1])
	{
		free(tmp);
		return ;
	}
}

void	add_to_env(t_shell *var, char *new_var)
{
	int		i;
	int		index_nv;
	char	**tmp;
	char	*new;
	int		flag;

	flag = 0;
	new = NULL;
	index_nv = eq_len(new_var);
	tmp = (char **)safe_malloc(sizeof(char *) * 2 + 1);
	add_env_supp(var, tmp, new_var, index_nv);
	i = 0;
	while (var->env[i])
	{
		if (ft_strncmp(var->env[i], new_var, index_nv) == 0)
		{
			flag = 1;
			new = add_to_env_supp_2(var, new, tmp, i);
			break ;
		}
		i++;
	}
	if (!flag)
		add_to_env_supp_3(var, new, tmp, i);
}
