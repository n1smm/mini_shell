/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:44:22 by tjuvan            #+#    #+#             */
/*   Updated: 2024/09/27 16:21:47 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*init(char *content, t_token **tail, t_token **head)
{
	t_token	*new_node;

	new_node = safe_malloc(sizeof(t_token));
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->content = content;
	new_node->typ_token = 0;
	new_node->trash = NULL;
	*tail = new_node;
	*head = new_node;
	return (new_node);
}

void	delete_node(t_token **tail, t_token *del, t_token **head)
{
	if (*tail == NULL || del == NULL)
		return ;
	if (*tail == del)
		*tail = del->next;
	if (*head == del)
		*head = del->prev;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
		del->prev->next = del->next;
	del->next = NULL;
	del->prev = NULL;
	free(del->content);
	free(del);
	del = NULL;
	return ;
}

t_token	*delete_node2(t_token **tail, t_token **del, t_token **head)
{
	t_token	*tmp;
	t_token	*prev;
	t_token	*next;

	tmp = *del;
	next = (*del)->next;
	prev = (*del)->prev;
	if (*tail == NULL || del == NULL)
		return (NULL);
	if (*tail == *del)
		*tail = (*del)->next;
	if (*head == *del)
		*head = (*del)->prev;
	if (next != NULL)
		next->prev = (*del)->prev;
	if (prev != NULL)
		prev->next = (*del)->next;
	free(tmp->content);
	free(tmp);
	return (*del);
}

int	find_token(t_token *tail, t_type type)
{
	t_token	*curr;
	int		i;

	curr = tail;
	i = 0;
	while (curr)
	{
		i++;
		if (curr->typ_token == type)
			return (i);
		curr = curr->next;
	}
	return (0);
}

char	*use_token(t_token **tail, t_type type)
{
	if (!tail || !*tail)
		return (NULL);
	while (*tail)
	{
		if ((*tail)->typ_token == type)
			return ((*tail)->content);
		if ((*tail)->next)
			*tail = (*tail)->next;
		else
			break ;
	}
	return (NULL);
}
