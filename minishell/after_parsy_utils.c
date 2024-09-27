#include "minishell.h"

int	check_quotes(t_token **tail)
{
	t_token	*curr;

	curr = *tail;
	while (curr)
	{
		if (curr->typ_token == FALSE_PLACEMENT)
		{
			printf("false placement of: %s\n", curr->content);
			return (0);
		}
		curr = curr->next;
	}
	return (1);
}

static int	check_after_delimiter(t_token *tmp, t_token *curr, bool *valid)
{
	while (tmp)
	{
		if (!is_delimiting_node(tmp))
			*valid = true;
		tmp = tmp->next;
	}
	if (!(*valid))
	{
		printf("invalid placement of: %s", curr->content);
		return (0);
	}
	return (1);
}

int	check_eol(t_token **tail)
{
	t_token	*curr;
	t_token	*tmp;
	bool	valid;

	curr = (*tail)->next;
	valid = false;
	while (curr)
	{
		if (is_delimiting_node(curr) && curr->typ_token != WHITESPACE)
		{
			tmp = curr;
			if (!check_after_delimiter(tmp, curr, &valid))
				return (0);
		}
		curr = curr->next;
		valid = false;
	}
	return (1);
}
