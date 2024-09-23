/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:00:05 by thiew             #+#    #+#             */
/*   Updated: 2024/09/23 08:52:18 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

static void	delete_quotes(t_token **tmp, t_token **tail, t_token **head,
		bool *special_boy)
{
	t_token	*curr;

	curr = *tmp;
	while (curr && !is_delimiting_node(curr))
	{
		if (is_quote_node(curr))
		{
			delete_node2(tail, &curr, head);
			*special_boy = true;
			curr = curr->prev;
		}
		curr = curr->next;
	}
	*tmp = (*tmp)->prev;
}

inline static void	place_content(t_token **tmp, char *content)
{
	free((*tmp)->content);
	(*tmp)->content = content;
}

static void	unite_infile(t_token **tmp, t_token **tail, t_token **head,
		bool *special_boy)
{
	t_token	*curr;
	char	*content;

	curr = *tmp;
	content = create_empty_string(1);
	while (curr && !is_file(curr))
		curr = curr->next;
	*tmp = curr;
	(*tmp)->special_boy = *special_boy;
	while (curr && !is_delimiting_node(curr))
	{
		content = join_wrapper(content, curr->content, 1);
		curr = curr->next;
	}
	place_content(tmp, content);
	curr = (*tmp)->next;
	while (curr && !is_delimiting_node(curr))
	{
		delete_node2(tail, &curr, head);
		curr = curr->next;
	}
}

void	check_files(t_token **tail, t_token **head)
{
	t_token	*curr;
	bool	special_boy;

	curr = *tail;
	special_boy = false;
	while (curr && curr->typ_token != PIPELINE)
	{
		if (is_redirect(curr))
		{
			while (curr && !is_file(curr) && !is_quote_node(curr))
				curr = curr->next;
			delete_quotes(&curr, tail, head, &special_boy);
			unite_infile(&curr, tail, head, &special_boy);
		}
		if (curr)
			curr = curr->next;
	}
	special_boy = special_boy;
}
