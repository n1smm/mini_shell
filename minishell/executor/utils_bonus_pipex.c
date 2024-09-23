/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_pipex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:47:41 by tjuvan            #+#    #+#             */
/*   Updated: 2024/09/23 10:18:07 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

void	here_doc_redirect(t_shell *data, t_token **tail, int i,
		bool special_boy)
{
	here_doc(data, tail, i, special_boy);
	data->file[i] = create_heredoc(data, i, 0);
	if (data->file[i] == -1)
		pid_error("here_doc; couldn't reopen file", NULL, 0);
	if (*tail)
		*tail = (*tail)->next;
}

int	eof_doc(char *input, char *limiter)
{
	if (!input || ((ft_strncmp(input, limiter, ft_strlen(limiter)) == 0)
			&& ft_strlen(input) == ft_strlen(limiter) + 1))
	{
		free(input);
		return (1);
	}
	return (0);
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
		if (eof_doc(input, limiter))
			break ;
		write(data->file[i], input, ft_strlen(input));
		free(input);
	}
	close(data->file[i]);
	input = get_next_line(data->file[i]);
	free(input);
}

int	create_heredoc(t_shell *data, int j, int create)
{
	int		fd;
	char	*file_name;
	char	*iteration;
	char	*pipe;

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
