/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:17:57 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/06/13 14:35:55 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	t_shell	status;
	if(sig == SIGINT)
	{
		status.running = false;
		//printf("prova");
	}
	else
		return ;
}
