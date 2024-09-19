/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:00:39 by thiew             #+#    #+#             */
/*   Updated: 2024/09/18 18:21:07 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_mtx(void **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

void free_tokens(t_token **tail, t_token **head)
{
    t_token *curr;
    t_token *next_node;

    while ((*tail)->prev)
        (*tail) = (*tail)->prev;
    if (*tail != NULL)
    {
        curr = *tail;
        while (curr->next != NULL)
        {
            next_node = curr->next;
            free(curr->content);
            free(curr);
            curr = next_node;
        }
        free(curr->content);
		free(curr);
    }
    t_token *new_node = safe_malloc(sizeof(t_token));
    if (new_node)
    {
        new_node->content = NULL;
        new_node->next = NULL;
        new_node->prev = NULL;
        new_node->typ_token = NONPRINTABLE;
        new_node->trash = NULL;
        *head = new_node;
        *tail = new_node;
        // add_to_garbage((*tail), new_node);
    }
    else
    {
        free(new_node);
        new_node = NULL;
    }
}

void free_tokens_final(t_token **tail, t_token **head)
{
    t_token *curr;
    t_token *next_node;

    while ((*tail)->prev)
        (*tail) = (*tail)->prev;
    if (*tail != NULL)
    {
        curr = *tail;
        while (curr != NULL)
        {
            next_node = curr->next;
            free(curr->content);
            free(curr);
            curr = next_node;
        }
		/* assert(*head == NULL && *tail == NULL); */
		printf("free tokens final: \n");
		print_list(curr);
		free(curr);
        *head = NULL;
        *tail = NULL;
    }
    // free (tail);
    // tail = NULL;
}

void	free_input_prompt(char *input, char *prompt)
{
	if (input)
		free(input);
	if (prompt)
		free(prompt);
}

void	error_handling(char *msg, int error_code)
{
	perror(msg);
	/* error_code = error_code; */
	g_error_code = error_code;
}
