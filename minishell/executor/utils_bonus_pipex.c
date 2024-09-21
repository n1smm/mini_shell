/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_pipex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:47:41 by tjuvan            #+#    #+#             */
/*   Updated: 2024/09/21 20:24:51 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

void	here_doc_redirect(t_shell *data, t_token **tail, int i, bool special_boy)
{
	here_doc(data, tail, i, special_boy);
	data->file[i] = create_heredoc(data, i, 0);
	if (data->file[i] == -1)
		pid_error("here_doc; couldn't reopen file", NULL, 0);
	if (*tail)
		*tail = (*tail)->next;
}

void	here_doc(t_shell *data, t_token **tail, int i, bool special_boy)
{
	char	*input;
	char	*limiter;

	if (!find_token(*tail, REDIRECT_IN_DOUBLE))
		return ;
	use_token(tail, LIMITER);
	special_boy = (*tail)->special_boy;
	limiter = (*tail)->content;
	while (1)
	{
		write(1, "heredoc> ", 9);
		input = get_next_line(0);
		if ((*tail)->special_boy == false)
			input = expand_string_checker(input, data, special_boy);
		if (!input || ((ft_strncmp(input, limiter, ft_strlen(limiter)) == 0)
				&& ft_strlen(input) == ft_strlen(limiter) + 1))
		{
			free(input);
			break ;
		}
		write(data->file[i], input, ft_strlen(input));
		free(input);
	}
	close(data->file[i]);
	input = get_next_line(data->file[i]);
	free(input);
}

int	create_heredoc(t_shell *data, int j, int create)
{
	int			fd;
	char		*file_name;
	char		*iteration;
	char		*pipe;
	
	pipe = ft_itoa(data->nbr_pipes);
	iteration = ft_itoa(j);
	if (j < 10)
		iteration = join_wrapper("0", iteration, 2);
	iteration = join_wrapper(pipe, iteration, 3);
	file_name = join_wrapper(".here_doc", iteration, 2);
	printf("heredoc filename: %s\n", file_name);
	if (create)
		fd = safe_open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (!create)
		fd = safe_open(file_name, O_RDONLY, 0644);
	free(file_name);

	return (fd);
}

void	delete_heredoc(t_shell *data, int i)
{
	char		*file_name;
	char		*iteration;
	char		*pipe;
	
	pipe = ft_itoa(data->nbr_pipes);
	iteration = ft_itoa(i);
	if (i < 10)
		iteration = join_wrapper("0", iteration, 0);
	iteration = join_wrapper(pipe, iteration, 2);
	file_name = join_wrapper(".here_doc", iteration, 2);
	if (unlink(file_name) == -1)
		printf("error unlinking %s", file_name); //exit safely
	free(file_name);
}

void	close_doc(t_shell *data, int file[], t_type file_type[], int delete)
{
	int	i;

	i = 0;
	while (file_type[i] != NONPRINTABLE)
	{
		if (file_type[i] != REDIRECT_IN_DOUBLE)
			close(file[i]);
		else
		{
			close(file[i]);
			if (delete)
				delete_heredoc(data, i);
		}
		i++;
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
	if (pipe == 1 && command == 0)
		return (-1);
	return (0);
}
