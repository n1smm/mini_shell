/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:03:55 by thiew             #+#    #+#             */
/*   Updated: 2024/09/26 16:47:42 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_env_vars(char **env)
{
	size_t	env_num;

	env_num = 0;
	while (env[env_num])
		env_num++;
	return (env_num);
}

static void	shell_iteration(t_shell **data, char **env, size_t *i)
{
	while (*i < (*data)->num_env_var)
	{
		(*data)->env[*i] = ft_strdup(env[*i]);
		if (!(*data)->env[*i])
		{
			free_garbage(&((*data)->garbage));
			*data = NULL;
			return ;
		}
		add_to_garbage(&((*data)->garbage), (*data)->env[*i]);
		(*i)++;
	}
	(*data)->env[(*data)->num_env_var] = NULL;
	*i = -1;
	while (++(*i) < (*data)->num_env_var)
	{
		(*data)->exp[*i] = ft_strdup_exp(env[*i]);
		if (!(*data)->exp[*i])
		{
			free_garbage(&((*data)->garbage));
			*data = NULL;
			return ;
		}
		add_to_garbage(&((*data)->garbage), (*data)->exp[*i]);
	}
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
	shell_iteration(data, env, &i);
	(*data)->exp[(*data)->num_env_var] = NULL;
	(*data)->next = NULL;
}

static void	last_iteration(const char *s, char *new_str, size_t *j, size_t *n)
{
	new_str[(*j)++] = '"';
	*n = *j - 1;
	while (s[*n])
	{
		new_str[*j] = s[*n];
		(*j)++;
		(*n)++;
	}
	new_str[(*j)++] = '"';
	new_str[(*j)++] = '\0';
}

char	*ft_strdup_exp(const char *s)
{
	char	*new_str;
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
		z++;
	new_str = (char *)safe_malloc(sizeof(char) * z + 3);
	while (s[j] && j <= eq)
	{
		new_str[j] = s[j];
		j++;
	}
	last_iteration(s, new_str, &j, &n);
	return ((char *)new_str);
}
