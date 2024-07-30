/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_pipex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:47:41 by tjuvan            #+#    #+#             */
/*   Updated: 2024/07/27 14:15:37 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

void	here_doc_redirect(int file[], t_token **tail, int i)
{
	here_doc(file, tail, i);
	file[i] = create_heredoc(i, 0);
	if (file[i] == -1)
		pid_error("here_doc; couldn't reopen file", NULL, 0);
	*tail = (*tail)->next;
}

void	here_doc(int file[], t_token **tail, int i)
{
	char	*input;
	char	*limiter;

	if (!find_token(*tail, REDIRECT_IN_DOUBLE))
		return ;
	limiter = use_token(tail, LIMITER)->content;
	while (1)
	{
		write(1, "heredoc> ", 9);
		input = get_next_line(0);
		input = expand_string_checker(input);
		if (!input || ((ft_strncmp(input, limiter, ft_strlen(limiter)) == 0)
				&& ft_strlen(input) == ft_strlen(limiter) + 1))
		{
			free(input);
			break ;
		}
		write(file[i], input, ft_strlen(input));
		free(input);
	}
	close(file[i]);
	input = get_next_line(file[i]);
	free(input);
}

int	create_heredoc(int j, int create)
{
	int			fd;
	char		*file_name;
	char		*iteration;
	
	iteration = ft_itoa(j);
	if (j < 10)
		iteration = join_wrapper("0", iteration, 0);
	file_name = join_wrapper(".here_doc", iteration, 2);
	printf("heredoc filename: %s\n", file_name);
	if (create)
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (!create)
		fd = open(file_name, O_RDONLY, 0644);

	return (fd);
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

int	check_pipe(t_token **tail, t_type file_type[])
{
	t_token *curr;
	int 	pipe;
	int		command;
	int		i;

	curr = *tail;
	pipe = 0;
	command = 0;
	i = -1;
	while(curr)
	{
		if (curr->typ_token == PIPELINE)
			pipe = 1;
		else if (pipe == 1 && curr->typ_token != PIPELINE && curr->typ_token != WHITESPACE)
			command = 1;
		curr = curr->next;
	} 
	while (file_type[++i] != NONPRINTABLE)
	{
		if(file_type[i] == REDIRECT_OUT || file_type[i] == REDIRECT_OUT_DOUBLE)
			command = 0;
	}
	if (pipe == 1 && command == 1)
		return(1);
	return (0);
}
