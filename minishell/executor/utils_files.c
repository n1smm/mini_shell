/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:59:41 by thiew             #+#    #+#             */
/*   Updated: 2024/09/03 14:08:54 by thiew            ###   ########.fr       */
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
