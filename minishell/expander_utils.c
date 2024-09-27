#include "minishell.h"

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

char	*ref_expand_str(char *content, t_shell *var, int start, int len)
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

void	refurbish_node(t_token *curr, char *content, bool free_me)
{
	int		i;
	bool	path;

	i = 0;
	path = false;
	free_me = free_me;
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
