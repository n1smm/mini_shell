/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:49:11 by thiew             #+#    #+#             */
/*   Updated: 2024/09/26 11:49:20 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

static void	check_len(char *content, int *j)
{
	int	len;

	len = ft_strlen(content);
	if (*j > len)
		*j = len;
	else if (content[*j] && content[*j] == '$')
		return ;
	else
	{
		while (content[*j] && content[*j] != '$')
			(*j)++;
	}
}

static void	expand_iteration(char *content, int *i, int *j)
{
	while (content[*i] != '$' && content[*i] != 0)
		(*i)++;
	if (content[*i])
		++(*i);
	*j = *i;
	while (content[*j] != 0 && (ft_isalnum(content[*j]) || content[*j] == '_'))
		(*j)++;
	if (*j == *i && content[*j] == '$')
		(*j)++;
	else if (*j == *i && content[*j] == '?')
		(*j)++;
}

void	expand_checker(t_token *curr, t_shell *var)
{
	char	*content;
	bool	free_me;
	int		i;
	int		j;

	i = 0;
	j = 0;
	free_me = true;
	content = curr->content;
	while (content[j])
	{
		i = 0;
		expand_iteration(content, &i, &j);
		content = ref_expand_str(content, var, i, j - i);
		check_len(content, &j);
		refurbish_node(curr, content, free_me);
		free_me = false;
	}
}

char	*expand_string_checker(char *content, t_shell *var, bool special_boy)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (special_boy == true || !content)
		return (content);
	while (content[j])
	{
		i = 0;
		while (content[i] != '$' && content[i] != 0)
			i++;
		if (content[i])
			++i;
		j = i;
		while (content[j] != 0 && (ft_isalnum(content[j]) || content[j] == '_'))
			j++;
		if (j == i && content[j] == '$')
			j++;
		content = ref_expand_str(content, var, i, j - i);
	}
	return (content);
}

char	*custom_getenv(char *name, char **env)
{
	int		i;
	size_t	name_len;

	if (name == NULL || env == NULL)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && \
			env[i][name_len] == '=')
		{
			return (&env[i][name_len + 1]);
		}
		i++;
	}
	return (NULL);
}

char	*expander(char *input, t_shell *var, t_type typ_token)
{
	char	*result;
	char	*result_path;

	var = var;
	if (typ_token == COMMAND)
	{
		result = path_finder(input, var);
		if (!result)
			return (NULL);
		return (result);
	}
	else if (typ_token == EXPAND)
	{
		result = custom_getenv(input, var->env);
		if (!result)
			return (NULL);
		result_path = ft_strdup(result);
		return (result_path);
	}
	return (NULL);
}
