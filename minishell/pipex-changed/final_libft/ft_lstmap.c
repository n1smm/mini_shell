/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:42:47 by tjuvan            #+#    #+#             */
/*   Updated: 2023/11/02 18:53:55 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*root;

	new = NULL;
	root = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst != NULL)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			while (root)
			{
				new = root->next;
				del(root->content);
				free(root);
				root = new;
			}
			return (NULL);
		}
		ft_lstadd_back(&root, new);
		lst = lst->next;
	}
	return (root);
}
