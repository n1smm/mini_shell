#include "minishell.h"

void    add_to_garbage(t_token *garbage, void *trash)
{
    t_trash *new_trash;

    new_trash = (t_trash *)safe_malloc(sizeof(t_trash));
    new_trash->content = trash;
    new_trash->next = garbage->trash;
    garbage->trash = new_trash;
}

void    free_garbage(t_token *garbage)
{
    if(!garbage || !garbage->trash)
        return ;
    t_trash *curr;
    t_trash *next;

    curr = garbage->trash;
    while(curr)
    {
        next = curr->next;
        free(curr->content);
        free(curr);
        curr = next;
    }
    garbage->trash = NULL;
}

void    safe_exit(t_token *garbage, int i)
{
    if (i == 1)
        printf("Error : 1");
    free_garbage(garbage);
}