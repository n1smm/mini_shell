/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:03:55 by thiew             #+#    #+#             */
/*   Updated: 2024/09/26 15:53:08 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/pipex.h"

size_t	count_env_vars(char **env)
{
	size_t	env_num;

	env_num = 0;
	while (env[env_num])
		env_num++;
	return (env_num);
}

void	ft_init_shell(t_shell **data, char **env)
{
	size_t	i;

	*data = (t_shell *)safe_malloc(sizeof(t_shell));
	(*data)->garbage.trash = NULL;
	(*data)->num_env_var = count_env_vars(env);
	(*data)->env = safe_malloc(sizeof(char *) * 1024);
	(*data)->exp = safe_malloc(sizeof(char *) * 1024);
	add_to_garbage(&((*data)->garbage), (*data)->env);
	add_to_garbage(&((*data)->garbage), (*data)->exp);
	add_to_garbage(&((*data)->garbage), *data);
	i = 0;
	while (i < (*data)->num_env_var)
	{
		(*data)->env[i] = ft_strdup(env[i]);
		if (!(*data)->env[i])
		{
			free_garbage(&((*data)->garbage));
			*data = NULL;
			return ;
		}
		add_to_garbage(&((*data)->garbage), (*data)->env[i]);
		i++;
	}
	(*data)->env[(*data)->num_env_var] = NULL;
	i = 0;
	while (i < (*data)->num_env_var)
	{
		(*data)->exp[i] = ft_strdup_exp(env[i]);
		if (!(*data)->exp[i])
		{
			free_garbage(&((*data)->garbage));
			*data = NULL;
			return ;
		}
		add_to_garbage(&((*data)->garbage), (*data)->exp[i]);
		i++;
	}
	(*data)->exp[(*data)->num_env_var] = NULL;
	(*data)->next = NULL;
}

char	*ft_strdup_exp(const char *s)
{
	char	*i;
	size_t	j;
	size_t	z;
	size_t	eq;
	size_t	n;

	if (!s)
		return (NULL);
	j = 0;
	z = 0;
	n = 0;
	eq = eq_len((char *)s);
	while (s[z])
	{
		z++;
	}
	i = (char *)malloc(sizeof(char) * z + 3);
	if (!i)
		return (NULL);
	while (s[j] && j <= eq)
	{
		i[j] = s[j];
		j++;
	}
	i[j++] = '"';
	n = j - 1;
	while (s[n])
	{
		i[j] = s[n];
		j++;
		n++;
	}
	i[j++] = '"';
	i[j++] = '\0';
	return ((char *)i);
}
