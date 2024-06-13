/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_pipex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:47:41 by tjuvan            #+#    #+#             */
/*   Updated: 2024/04/08 19:22:42 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(int file[], char **argv)
{
	char	*input;

	if (ft_strncmp(argv[1], "here_doc", 9) != 0)
		return ;
	while (1)
	{
		write(1, "heredoc> ", 9);
		input = get_next_line(0);
		if (!input || (ft_strncmp(input, argv[2], ft_strlen(argv[2])) == 0
				&& ft_strlen(input) == ft_strlen(argv[2]) + 1))
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
		pid_error("here_doc; coulnd't reopen file", NULL, 0);
}

void	unlink_doc(char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		if (unlink(".here_doc") == -1)
			perror("unlink failed");
	}
}
