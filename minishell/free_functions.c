/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:00:39 by thiew             #+#    #+#             */
/*   Updated: 2024/06/13 14:28:27 by thiew            ###   ########.fr       */
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

    if (*head != NULL)
    {
        curr = *head;
        while (curr != NULL)
        {
            next_node = curr->next;
            free(curr->content);
            free(curr);
            curr = next_node;
        }
        *head = NULL;
        *tail = NULL;
    }
}
void	free_input_prompt(char *input, char *prompt)
{
	if (input)
		free(input);
	if (prompt)
		free(prompt);
}

// void free_tokens(t_token **head)
// {
//     t_token *current;
//     t_token *next;

//     next = NULL;
//     current = *head;
//     *head = NULL;
//     while (current)
//     {
//         next = current->next;
//         if (current->content)
//         {
//             free(current->content);
//             current->content = NULL;
//         }
//         free(current);
//         current = next;   
//     }
// }
