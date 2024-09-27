/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:50:22 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/09/27 18:51:46 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_len(char *content, int *j)
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

static char	*error_expansions(char *expanded)
{
	char	*result;

	result = ft_itoa(g_error_code);
	if (!result)
	{
		error_handling("expansion of ? failed, exiting program", errno);
		exit(errno);
	}
	free(expanded);
	return (result);
}

char	*ref_expand_str_supp(char *result, char *content)
{
	result = strdup(content);
	return (result);
}

char	*ref_expand_str(char *content, t_shell *var, int start, int len)
{
	char	*expanded;
	char	*result;
	char	*contentcpy;

	result = NULL;
	if (!len)
		return (ref_expand_str_supp(result, content));
	expanded = ft_substr(content, start, len);
	if (expanded[0] == '?')
	{
		result = error_expansions(expanded);
		free(content);
		return (result);
	}
	result = expander(expanded, var, EXPAND);
	if (!result)
		result = create_empty_string(1);
	free(expanded);
	expanded = ft_strdup(content + (start + len));
	contentcpy = ft_substr(content, 0, start - 1);
	result = join_wrapper(contentcpy, result, 2);
	result = join_wrapper(result, expanded, 3);
	free(content);
	free(contentcpy);
	return (result);
}

void	refurbish_node(t_token *curr, char *content)
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
	curr->content = content;
}
