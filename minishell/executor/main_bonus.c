/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:19:41 by thiew             #+#    #+#             */
/*   Updated: 2024/08/04 14:19:02 by tjuvan           ###   ########.fr       */
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
	if (ft_strncmp(input[0], "cd", 3) == 0)
	{
		ft_cd(input[1]);
		return (1);
	}
	else if(ft_strncmp(input[0], "env", 3) == 0)
	{
		ft_env(data);
		return (1);
	}
	else if(ft_strncmp(input[0], "export", 6) == 0)
	{
		ft_export(data, input);
		return (1);
	}
	else if(ft_strncmp(input[0], "unset", 5) == 0)
	{
		ft_unset(data, input);
		return (1);
	}
	else if(ft_strncmp(input[0], "pwd", 3) == 0)
	{
		ft_pwd();
		return (1);
	}
	else if(ft_strncmp(input[0], "echo", 4) == 0)
	{
		ft_echo(input);
		return (1);
	}
	else if(path_finder(input[0]))
		return(0);
	else
	{
		write(2, "xxx",3);
		write(2, "\n",1);
		printf("command not found: No such file or directory\n");
		exit(EXIT_FAILURE);
		return (-1);
	}
}

t_token	*assign_special_boy(t_token *tmp)
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

void	check_redirects(t_token **tail)
{
	t_token	*curr;
	t_token	*tmp;

	curr = *tail;
	while(curr && curr->typ_token != PIPELINE)
	{
		if (curr->typ_token == REDIRECT_IN ||  curr->typ_token == REDIRECT_OUT || curr->typ_token == REDIRECT_IN_DOUBLE || curr->typ_token == REDIRECT_OUT_DOUBLE)
		{
			tmp = assign_special_boy(curr);
			while (curr && curr->typ_token != WHITESPACE && curr->typ_token != PIPELINE)
			{
				if (curr->typ_token == QUOTE || curr->typ_token == SINGLE_QUOTE)
				{
					if(tmp)
						tmp->special_boy = true;
					tmp = curr->next;
					delete_node(tail, curr);
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

char	**pipe_loop(t_token **tail)
{
	char	*path;
	char	**command_seq;

	if (!tail || !*tail)
		return (NULL);
	path = path_finder(use_token(tail, COMMAND)->content);
	if (path == NULL)
	{
		;//printf("command not found: No such file or direcotry\n");
		//pid_error("command not found", NULL, 0);
	}
	free(path);
	command_seq = seq_extract(tail);
	return (command_seq);
}

int	new_executor(t_token **tail, t_shell *data)
{
	/* int			pipefd[4]; */
	/* int			file[1024]; */
	/* t_type		file_type[1024]; */
	t_token		*tmp;
	char		**comm_seq;

	tmp = *tail;
	data->pipefd[2] = dup(0);//safe_dup(0, 0, 0);
	data->pipefd[3] = dup(1);//safe_dup(1, 1, 0);
	//printf("fd2: %d, fd3: %d\n",data->pipefd[2], data->pipefd[3]);
	data->file[1023] = 0;
	while (*tail)
	{
		check_redirects(tail);
		files_open(tail, data);
		comm_seq = pipe_loop(tail);
		if (check_pipe(tail, data->file_type) == 0)
			data->file[1023] = execute_comm(comm_seq, data);
		if (data->file[1023] == 0)
			comm_forker(comm_seq , data, check_pipe(tail, data->file_type), &tmp);
		close_doc(data->file, data->file_type, 0);
		if ( *tail && (*tail)->typ_token == PIPELINE)
			*tail = (*tail)->next;
	}
	safe_dup(data->pipefd[2], 0, 1);
	safe_dup(data->pipefd[3], 1, 1);
	*tail = tmp;
	waiting_pids(tail, data->file[1023]);
	return(0);
}

// /* old executor */
// int	old_executor(t_token **tail, char **envp)
// {
// 	int			pipefd[4];
// 	int			file[1024];
// 	t_type		file_type[1024];
// 	t_token		*tmp;
// 	char		**comm_seq;
// 	/* int i; */

// 	tmp = *tail;
// 	pipefd[2] = dup(0);
// 	pipefd[3] = dup(1);
// 	while (*tail) // || (*tail)->typ_token != REDIRECT_OUT || (*tail)->typ_token != REDIRECT_OUT_DOUBLE)
// 	{
// 		/* i = 0; */
// 		files_open(file, file_type, tail, pipefd);
// 		if (file_type[0] != PRINTABLE)
// 			redirect_infiles(file, file_type, tail);
// 		comm_seq = pipe_loop(tail);
// 		/* while (comm_seq[i]) */
// 		/* { */
// 		/* 	printf("comm_seq[%d]: %s \n", i, comm_seq[i]); */
// 		/* 	i++; */
// 		/* } */
// 		comm_forker(comm_seq , envp, pipefd, check_pipe(tail, file_type));
// 		if ( *tail && (*tail)->typ_token == PIPELINE)
// 			*tail = (*tail)->next;
// 	}
// 	/* if (dup2(file[0], STDOUT_FILENO) == -1) */
// 	/* 	pid_error("outfile dup failed", NULL, 0); */
// 	dup2(pipefd[2], 0);
// 	dup2(pipefd[3], 1);
// 	/* if (dup2(pipefd[0], STDOUT_FILENO) == -1) */
// 	/* 	pid_error("dup2 to stdout failed", NULL, 0); */
// 	/* close(pipefd[0]); */
// 	*tail = tmp;
// 	/* close(file[0]); */
// 	/* unlink_doc(*tail); */
// 	/* last = ft_split(seq_extract(tail), ' '); */
// 	/* if (dup2(file[1], STDOUT_FILENO) == -1) */
// 	/* 	pid_error("outfile dup failed", NULL, 0); */
// 	/* execve(path_finder(last[0]), last, envp); */
// 	/* free_mtrx(last); */
// 	/* pid_error("last exec failed", NULL, 0); */
// 	return(0);
// }
