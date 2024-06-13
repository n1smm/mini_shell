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

void	free_tokens(t_token **tail, t_token **head, int	final_free)
{			
	t_token	*curr;
	t_token	*next_node;
	char *place_holder;

	curr = NULL;
	next_node = NULL;
	if (*tail != NULL || *head != NULL)
	{
		curr = *tail;
		while (curr->next != NULL)
		{
			next_node = curr->next;
			free(curr->content);
			free(curr);
			curr = next_node;
		}
		free(curr);
	}
	if (final_free)
	{
		free(tail);
		free(head);
	}
	else
	{
		place_holder = malloc(1);
		place_holder[0] = 0;
		curr = init(place_holder, tail, head);
		curr->typ_token = NONPRINTABLE;
	}
}
		


