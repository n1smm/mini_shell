/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:49:11 by thiew             #+#    #+#             */
/*   Updated: 2024/08/03 13:00:28 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

/* if the type of token is correct it will allocate, 
otherwise it returns null not allocated */
char	*expander(char *input, t_type typ_token)
{
	char	*result;
	char	*result_path;

	if (typ_token == COMMAND)
	{
		result = path_finder(input, var->env);
		if (!result)
			return (NULL);
		return (result);
	}
	else if (typ_token == EXPAND)
	{
		result = getenv(input);
		if (!result)
			return (NULL);
		result_path = ft_strdup(result);
		return (result_path);
	}
	return (NULL);
}

static char	*refactor_expanded_string(char *content, int start, int len)
{
	char	*expanded;
	char	*result;
	char	*contentcpy;

	if (!len)
	{
		result = strdup(content);
		return (result);
	}
	expanded = ft_substr(content, start, len);
	result = expander(expanded, EXPAND);
	if (!result)
		result = create_empty_string(1);
	free(expanded);
	expanded = ft_strdup(content + (start + len));
	contentcpy = ft_substr(content, 0, start - 1);
	result = join_wrapper(contentcpy, result, 2);
	result = join_wrapper(result, expanded, 3);
	return (result);
}

static void	refurbish_node(t_token *curr, char *content, bool free_me)
{
	int		i;
	bool	path;

	i = 0;
	path = false;
	curr->typ_token = WORD;
	while (content[i])
	{
		if (!ft_isalpha(content[i]))
			curr->typ_token = STRING;
		if (content[i++] == '/')
			path = true;
	}
	if (path)
		curr->typ_token = PATH;
	if (free_me)
		free(curr->content);
	curr->content = content;
}

void	expand_checker(t_token *curr)
{
	char	*content;
	bool	free_me;
	int		i;
	int		j;

	i = 0;
	j = 0;
	free_me = false;
	content = curr->content;
	//printf("content: %s\n", content);
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
		content = refactor_expanded_string(content, i, j - i);
		refurbish_node(curr, content, free_me);
		free_me = true;
	}
}

char	*expand_string_checker(char *content, bool special_boy)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (special_boy == false)
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
		content = refactor_expanded_string(content, i, j - i);
	}
	return (content);
}
