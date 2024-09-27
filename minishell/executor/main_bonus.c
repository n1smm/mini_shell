/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:19:41 by thiew             #+#    #+#             */
/*   Updated: 2024/09/27 18:53:39 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

void	free_mtrx(char **mtrx)
{
	int	i;

	i = 0;
	while (mtrx[i] != 0)
	{
		free(mtrx[i]);
		i++;
	}
	free(mtrx[i]);
	free(mtrx);
}

void	pid_error(char *msg, char **str, int free_me)
{
	perror(msg);
	exit(EXIT_FAILURE);
	if (free_me == 1)
		free(*str);
}

char	**pipe_loop(t_token **tail)
{
	char	**command_seq;
	char	*tmp;

	if (!tail || !*tail)
		return (NULL);
	if (find_token(*tail, PRINTABLE) != 0 && find_token(*tail,
			PRINTABLE) < find_token(*tail, COMMAND))
		tmp = ft_strdup(use_token(tail, PRINTABLE));
	else
		tmp = ft_strdup(use_token(tail, COMMAND));
	if (tmp)
	{
		free(tmp);
	}
	command_seq = seq_extract(tail);
	return (command_seq);
}

int	new_executor(t_token **tail, t_shell *data, t_token **head)
{
	t_token	*tmp2;
	t_token	*tmp3;
	char	**comm_seq;

	tmp3 = *tail;
	init_fds(data);
	while (*tail)
	{
		tmp2 = *tail;
		if (!init_files(tail, head, data, &comm_seq))
			break ;
		if (check_pipe(tail, data->file_type) == 0)
		{
			if (is_builtin(comm_seq))
				redirect_infiles(data, data->file, data->file_type, &tmp2);
			data->file[1023] = execute_comm(comm_seq, data, &tmp3, head);
		}
		if (data->file[1023] == 0 || data->file[1023] == 2)
			comm_forker(comm_seq, data, check_pipe(tail, data->file_type),
				&tmp2);
		close_and_free(data, tail, comm_seq);
	}
	return (polish_pipes(data, tail, tmp3));
}
