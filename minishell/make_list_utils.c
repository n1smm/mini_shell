#include "minishell.h"

bool	double_lstadd_front(char *content, t_token **tail)
{
	t_token	*curr;
	t_token	*new;

	new = safe_malloc(sizeof(t_token));
	curr = *tail;
	if (*tail == NULL)
	{
		free(new);
		return (-1);
	}
	new->content = content;
	new->next = curr;
	new->trash = NULL;
	curr->prev = new;
	*tail = new;
	return (true);
}

bool	double_lstadd_back(char *content, t_token **head)
{
	t_token	*curr;
	t_token	*new;

	if (!head)
		return (-1);
	curr = *head;
	new = safe_malloc(sizeof(t_token));
	if (*head == NULL)
	{
		free(new);
		return (-1);
	}
	new->content = content;
	new->next = NULL;
	new->prev = curr;
	new->trash = NULL;
	curr->next = new;
	*head = new;
	return (true);
}
