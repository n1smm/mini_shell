/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:26:17 by tjuvan            #+#    #+#             */
/*   Updated: 2023/11/01 16:09:36 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	tmp = NULL;
	curr = *lst;
	while (curr != NULL)
	{
		tmp = curr->next;
		ft_lstdelone(curr, del);
		curr = tmp;
	}
	*lst = NULL;
}
