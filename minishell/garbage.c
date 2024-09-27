/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:49:49 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/09/27 14:49:49 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_garbage(t_token *garbage, void *trash)
{
	t_trash	*new_trash;

	if (!garbage || !trash)
		return ;
	new_trash = (t_trash *)safe_malloc(sizeof(t_trash));
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

void	free_garbage_tail(t_token *garbage)
{
	t_trash	*curr;
	t_trash	*next;

	if (!garbage)
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
}

void	safe_exit(t_token *garbage, int i)
{
	if (i == 1)
		printf("Error : 1");
	free_garbage(garbage);
}
