#include "minishell.h"


void add_to_garbage(t_trash *garbage, void *trash)
{
    t_trash	*new_trash;

    new_trash = safe_malloc(sizeof(t_trash));
    //new_trash = trash;
    if (!garbage || !garbage->next)
        garbage = new_trash;
    else
    {
        while (garbage->next)
        {
            garbage = garbage->next;
        }
        garbage->next = new_trash;
    }
    new_trash->content = trash;
    new_trash->next = NULL;
	free(trash);
}

void	free_garbage(t_trash *garbage)
{
	t_trash	*curr;
	t_trash	*next;

	if (!garbage)
		return ;
	curr = garbage;
	if (!curr)
		return ;
	//next = NULL;
	while (curr)
	{
		next = curr->next;
		if (curr->content)
		{
			free(curr->content);
			//curr->content = NULL;
		}
		curr = next;
	}
	free(curr);
	// garbage->trash = NULL;
}

void	safe_exit(t_token *garbage, int i)
{
	if (i == 1)
		printf("Error : 1");
	free_garbage(garbage->trash);
}
