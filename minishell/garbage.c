#include "minishell.h"

// void add_to_garbage2(t_token *garbage, void *trash)
// {
// 	if(!garbage || !trash)
// 		return ;
// 	garbage->last_trash = trash;
// }

void add_to_garbage(t_token *garbage, void *trash)
{
    t_trash *new_trash;

    if (!garbage || !trash)
        return;

    new_trash = (t_trash *)safe_malloc(sizeof(t_trash));
    new_trash->content = trash;
    new_trash->next = garbage->trash;
    garbage->trash = new_trash;
	// free(new_trash);
}

// void	free_new_trash(void *trash)
// {
// 	free(trash);
// 	trash = NULL;
// }

void	free_garbage(t_token *garbage)
{
	t_trash	*curr;
	t_trash	*next;

	if (!garbage || !garbage->trash)
		return ;
	curr = garbage->trash;
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
	// printf ("%p\n", curr->content);
	//printf ("%p\n", curr);
	// free_new_trash(&curr->content);

	// garbage->trash = NULL;
}


void	safe_exit(t_token *garbage, int i)
{
	if (i == 1)
		printf("Error : 1");
	free_garbage(garbage);
}
