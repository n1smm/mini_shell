/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_pipex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:47:41 by tjuvan            #+#    #+#             */
/*   Updated: 2024/07/16 17:59:11 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(int file[], t_token **tail)
{
	char	*input;
	char	*limiter;

	if (find_token(*tail, REDIRECT_IN_DOUBLE) == -1)
		return ;
	limiter = use_token(tail, LIMITER)->content;
	while (1)
	{
		write(1, "heredoc> ", 9);
		input = get_next_line(0);
		if (!input || ((ft_strncmp(input, limiter, ft_strlen(limiter)) == 0)
				&& ft_strlen(input) == ft_strlen(limiter) + 1))
		{
			free(input);
			break ;
		}
		write(file[0], input, ft_strlen(input));
		free(input);
	}
	close(file[0]);
	input = get_next_line(file[0]);
	free(input);
	file[0] = open(".here_doc", O_RDONLY, 0644);
	if (file[0] == -1)
		pid_error("here_doc; couldn't reopen file", NULL, 0);
}

void	unlink_doc(t_token *tail)
{
	/* if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0) */
	if (find_token(tail, REDIRECT_IN_DOUBLE) == -1)
	{
		if (unlink(".here_doc") == -1)
			perror("unlink failed");
	}
}
