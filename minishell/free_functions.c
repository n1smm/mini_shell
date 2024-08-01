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

void	free_tokens(t_token **tail, t_token **head, int final_free)
{
	t_token	*curr;
	t_token	*next_node;
	t_token	*new_node;

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
	if (final_free)
	{
		free(tail);
		free(head);
	}
	else
	{
		new_node = malloc(sizeof(t_token));
		if (new_node)
		{
			new_node->content = malloc(1);
			if (new_node->content)
			{
				new_node->content[0] = 0;
				new_node->next = NULL;
				new_node->prev = NULL;
				new_node->typ_token = NONPRINTABLE;
				new_node->trash = NULL;
				*head = new_node;
				*tail = new_node;
			}
			else
			{
				free(new_node);
				*tail = NULL;
				*head = NULL;
			}
		}
	}
}
