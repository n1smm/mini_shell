/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:50:32 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/09/27 16:21:14 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_to_export2_supp(t_shell *var, int *i, const char *new_var)
{
	var->exp[*i] = (char *)safe_malloc(sizeof(char) * \
		ft_strlen(new_var) + 1);
	add_to_garbage(&(var->garbage), var->exp[*i]);
	var->exp[*i] = ft_strdup(new_var);
	add_to_garbage(&(var->garbage), var->exp[*i]);
}

void	add_to_export2(t_shell *var, char *new_var)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	j = 0;
	if (!var || ! new_var)
		return ;
	flag = 0;
	while (var->exp[i])
	{
		j = eq_len(var->exp[i]);
		if ((ft_strncmp(var->exp[i], new_var, j) == 0) && var->exp[i])
		{
			flag = 1;
			var->exp[i] = ft_strdup(var->exp[i]);
			add_to_garbage(&(var)->garbage, var->exp[i]);
		}
		i++;
	}
	if (flag == 0)
		add_to_export2_supp(var, &i, new_var);
	var->exp[i + 1] = NULL;
	add_to_garbage(&(var->garbage), var->exp[i + 1]);
}

static void	add_to_export_supp(t_shell *var, char **tmp, char *new, int *i)
{
	new = ft_strjoin_exp(tmp[0], tmp[1]);
	add_to_garbage(&(var)->garbage, new);
	var->exp[*i] = ft_strdup(new);
	add_to_garbage(&(var)->garbage, var->exp[*i]);
	var->exp[*i + 1] = NULL;
	add_to_garbage(&(var)->garbage, var->exp[*i + 1]);
}

static void	add_exp_supp_2(t_shell *var, char **tmp, char *new_var, int i_nv)
{
	tmp[0] = ft_substr(new_var, 0, i_nv + 1);
	add_to_garbage(&(var)->garbage, tmp[0]);
	tmp[1] = ft_substr(new_var, i_nv + 1, ft_strlen(new_var));
	add_to_garbage(&(var)->garbage, tmp[1]);
}

void	add_to_export(t_shell *var, char *new_var)
{
	int		i;
	int		index_nv;
	char	**tmp;
	char	*new;
	int		flag;

	flag = 0;
	i = 0;
	new = NULL;
	index_nv = eq_len(new_var);
	tmp = (char **)safe_malloc(sizeof(char *) * 2 + 1);
	add_to_garbage(&(var)->garbage, tmp);
	add_exp_supp_2(var, tmp, new_var, index_nv);
	while (var->exp[i])
	{
		if (ft_strncmp(var->exp[i], new_var, index_nv) == 0)
		{
			flag = 1;
			add_to_export_supp(var, tmp, new, &i);
			break ;
		}
		i++;
	}
	if (!flag)
		add_to_export_supp(var, tmp, new, &i);
}
