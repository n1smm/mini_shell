#include "includes/minishell.h"

t_token	*init_shell(t_shell **tail, t_shell **head)
{
	t_token	*new_node;

	new_node = safe_malloc(sizeof(t_token));
	/* if (!new_node) */
	/* 	return (NULL); */
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->typ_token = 0;
	*tail = new_node;
	*head = new_node;
	return (new_node);
}