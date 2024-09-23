/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:59:41 by thiew             #+#    #+#             */
/*   Updated: 2024/09/23 09:56:41 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

void	redirect_in(t_token *curr, int *i, t_shell *data)
{
	while (curr && !is_file(curr))
		curr = curr->next;
	safe_dup(data->pipefd[2], 0, 1);
	data->file[*i] = create_heredoc(data, *i, 1);
	data->file_type[(*i)++] = REDIRECT_IN_DOUBLE;
}

int	redirect_out(t_token *curr, int *i, t_shell *data)
{
	while (curr && !is_file(curr))
		curr = curr->next;
	data->file[*i] = safe_open(curr->content, O_WRONLY | O_CREAT | O_TRUNC,
			0666);
	if (data->file[*i] == -1)
		return (0);
	data->file_type[(*i)++] = REDIRECT_OUT;
	return (1);
}

int	init_files(t_token **tail, t_token **head, t_shell *data, char ***comm_seq)
{
	data->nbr_pipes = count_pipes(*tail);
	check_files(tail, head);
	if (!files_open(tail, data))
		return (0);
	*comm_seq = pipe_loop(tail, data);
	return (1);
}

void	delete_heredoc(t_shell *data, int i)
{
	char	*file_name;
	char	*iteration;
	char	*pipe;

	pipe = ft_itoa(data->nbr_pipes);
	iteration = ft_itoa(i);
	if (i < 10)
		iteration = join_wrapper("0", iteration, 0);
	iteration = join_wrapper(pipe, iteration, 2);
	file_name = join_wrapper(".here_doc", iteration, 2);
	if (unlink(file_name) == -1)
		printf("error unlinking %s", file_name);
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
