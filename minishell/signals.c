/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:17:57 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/06/13 16:56:40 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_signals()
{
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, &ctrl_slash);
}

void	ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
	}
	else
		return ;
}

void	ctrl_slash(int sig)
{
	struct termios	term;

	sig = sig;
	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;// Disable the quit character
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
