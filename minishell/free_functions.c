/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:00:39 by thiew             #+#    #+#             */
/*   Updated: 2024/05/21 16:01:13 by thiew            ###   ########.fr       */
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
