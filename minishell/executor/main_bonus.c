/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:19:41 by thiew             #+#    #+#             */
/*   Updated: 2024/08/07 23:41:43 by tjuvan           ###   ########.fr       */
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
	free(mtrx);
}

void	pid_error(char *msg, char **str, int free_me)
{
	perror(msg);
	exit(EXIT_FAILURE);
	if (free_me == 1)
		free(*str);
}

int	execute_comm(char **input, t_shell *data)
{
	if (!input[0])
		return (-1);
	// exit safely
	if (ft_strncmp(input[0], "cd", ft_strlen(input[0])) == 0)
	{
		ft_cd(input[1]);
		return (1);
	}
	else if(ft_strncmp(input[0], "env", ft_strlen(input[0])) == 0)
	{
		ft_env(data);
		return (1);
	}
	else if(ft_strncmp(input[0], "export", ft_strlen(input[0])) == 0)
	{
		ft_export(data, input);
		return (1);
	}
	else if(ft_strncmp(input[0], "unset", ft_strlen(input[0])) == 0)
	{
		ft_unset(data, input);
		return (1);
	}
	else if(ft_strncmp(input[0], "pwd", ft_strlen(input[0])) == 0)
	{
		ft_pwd();
		return (1);
	}
	else if(ft_strncmp(input[0], "echo", ft_strlen(input[0])) == 0)
	{
		ft_echo(input);
		return (1);
	}
	else if(path_finder(input[0], data))
		return(0);
	else if (ft_strchr(input[0], '/'))
		return(2);
	else
	{
		write(2, "xxx",3);
		write(2, "\n",1);
		printf("command not found: No such file or directory\n");
		/* exit(EXIT_FAILURE); */
		return (-1);
	}
}

t_token	*find_special_boy(t_token *tmp)
{
	t_token *curr;

	curr = tmp;
	while (curr && curr->typ_token != WHITESPACE && curr->typ_token != PIPELINE)
	{
		if (curr->typ_token == LIMITER)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

void	assign_special_boy(t_token **tail, t_token **head, t_token **curr, t_token **tmp)
{
	if(*tmp)
		(*tmp)->special_boy = true;
	*tmp = (*curr)->next;
	delete_node(tail, *curr, head);
	*curr = *tmp;
	*tmp = NULL;
}
void	check_redirects(t_token **tail, t_token **head)
{
	t_token	*curr;
	t_token	*tmp;

	curr = *tail;
	while(curr && curr->typ_token != PIPELINE)
	{
		if (curr->typ_token == REDIRECT_IN ||  curr->typ_token == REDIRECT_OUT || curr->typ_token == REDIRECT_IN_DOUBLE || curr->typ_token == REDIRECT_OUT_DOUBLE)
		{
			tmp = find_special_boy(curr);
			while (curr && curr->typ_token != WHITESPACE && curr->typ_token != PIPELINE)
			{
				if (curr->typ_token == QUOTE || curr->typ_token == SINGLE_QUOTE)
				{
					assign_special_boy(tail, head, &curr, &tmp);
					if(tmp)
						tmp->special_boy = true;
					tmp = curr->next;
					delete_node(tail, curr, head);
					curr = tmp;
					tmp = NULL;
				}
				curr = curr->next;
			}
		}
		if (curr)
			curr = curr->next;
	}
}

char	**pipe_loop(t_token **tail, t_shell *data)
{
	char	*path;
	char	**command_seq;
	char	*tmp;

	if (!tail || !*tail)
		return (NULL);
	if(find_token(*tail, PRINTABLE) != 0 && find_token(*tail, PRINTABLE) < find_token(*tail, COMMAND))
			tmp = ft_strdup(use_token(tail, PRINTABLE));
	else
		tmp = ft_strdup(use_token(tail, COMMAND));
	if (tmp)
	{
		path = path_finder(tmp, data);
		if (path == NULL)
		{
			;
		}
		free(path);
	}
	command_seq = seq_extract(tail);
	return (command_seq);
}

int	new_executor(t_token **tail, t_shell *data, t_token **head)
{
	t_token		*tmp;
	t_token		*tmp2;
	char		**comm_seq;

	tmp = *tail;
	data->pipefd[2] = dup(0);
	data->pipefd[3] = dup(1);
	data->file[1023] = 0;
	while (*tail)
	{
		tmp2 = *tail;
		data->nbr_pipes = count_pipes(*tail);
		check_redirects(tail, head);
		files_open(tail, data);
		comm_seq = pipe_loop(tail, data);
		if (check_pipe(tail, data->file_type) == 0)
			//here i need to put also redirect files
			data->file[1023] = execute_comm(comm_seq, data);
		if (data->file[1023] == 0 || data->file[1023] == 2)
			comm_forker(comm_seq , data, check_pipe(tail, data->file_type), &tmp2);
		close_doc(data, data->file, data->file_type, 0);
		if ( *tail && (*tail)->typ_token == PIPELINE)
			*tail = (*tail)->next;
	}
	safe_dup(data->pipefd[2], 0, 1);
	safe_dup(data->pipefd[3], 1, 1);
	*tail = tmp;
	waiting_pids(tail, data->file[1023]);
	return(0);
}
