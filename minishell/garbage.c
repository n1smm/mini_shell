#include "minishell.h"

void cleanup(t_token *head)
{
    t_token *current = head;
    t_token *next;

    while (current)
    {
        next = current->next;
        free_garbage(current);
        free(current->content);  // If content is not part of garbage collection
        free(current);
        current = next;
    }
}

void add_to_garbage(t_token *garbage, void *trash)
{
    t_trash *new_trash;

    if (!garbage || !trash)
        return;

    new_trash = (t_trash *)safe_malloc(sizeof(t_trash));
    if (!new_trash)
        return;
    new_trash->content = trash;
    new_trash->next = garbage->trash;
    garbage->trash = new_trash;
}

void	free_garbage(t_token *garbage)
{
	t_trash	*curr;
	t_trash	*next;

	if (!garbage)
		return ;
	curr = garbage->trash;
	if (!curr)
		return ;
	garbage->trash = NULL;
	while (curr)
	{
		next = curr->next;
		if (curr->content)
		{
			free(curr->content);
			curr->content = NULL;
		}
		free(curr);
		curr = next;
	}
}

void	safe_exit(t_token *garbage, int i)
{
	if (i == 1)
		printf("Error : 1");
	free_garbage(garbage);
}
