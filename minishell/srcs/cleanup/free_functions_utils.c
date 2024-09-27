/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:49:55 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/09/27 16:18:24 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	error_handling(char *msg, int error_code)
{
	perror(msg);
	g_error_code = error_code;
}
