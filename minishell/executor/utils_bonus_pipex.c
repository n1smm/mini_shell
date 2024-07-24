/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_pipex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:47:41 by tjuvan            #+#    #+#             */
/*   Updated: 2024/07/22 19:08:38 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

void	here_doc(int file[], t_token **tail)
{
	char	*input;
	char	*limiter;
	t_token	*curr;

	curr = *tail;
	if (!find_token(curr, REDIRECT_IN_DOUBLE))
		return ;
	limiter = use_token(&curr, LIMITER)->content;
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

int	check_pipe(t_token **tail)
{
	t_token *curr;
	int 	pipe;
	int		command;

	curr = *tail;
	pipe = 0;
	command = 0;
	while(curr)
	{
		if (curr->typ_token == PIPELINE)
			pipe = 1;
		else if (pipe == 1 && curr->typ_token != PIPELINE && curr->typ_token != WHITESPACE)
			command = 1;
		curr = curr->next;
	} 
	if (pipe == 1 && command == 1)
		return(1);
	return (0);
}
