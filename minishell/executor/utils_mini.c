/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:03:52 by tjuvan            #+#    #+#             */
/*   Updated: 2024/08/03 16:41:05 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

void	waiting_pids(t_token **tail, int builtin)
{
	t_token *curr;

	curr = *tail;
	if (!builtin)
		wait(NULL);
	while (curr)
	{
		if (curr->typ_token == PIPELINE)
			wait(NULL);
		curr = curr->next;
	}
}
