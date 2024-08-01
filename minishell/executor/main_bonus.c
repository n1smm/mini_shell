/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:19:41 by thiew             #+#    #+#             */
/*   Updated: 2024/08/01 20:24:14 by tjuvan           ###   ########.fr       */
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

int	cmd_exists(char **input)
{
	if(ft_strncmp(input[0], "ls", 2) == 0 || \
		ft_strncmp(input[0], "chmod", 5) == 0 || \
			ft_strncmp(input[0], "read", 4) == 0 || \
				ft_strncmp(input[0], "mkdir", 5) == 0 || \
					ft_strncmp(input[0], "touch", 5) == 0 || \
						ft_strncmp(input[0], "rm", 2) == 0 || \
							ft_strncmp(input[0], "cp", 2) == 0 || \
								ft_strncmp(input[0], "mv", 2) == 0 || \
									ft_strncmp(input[0], "cat", 3) == 0 || \
										ft_strncmp(input[0], "grep", 4) == 0 || \
											ft_strncmp(input[0], "sudo", 4) == 0 || \
												ft_strncmp(input[0], "df", 2) == 0 || \
													ft_strncmp(input[0], "history", 7) == 0 || \
														ft_strncmp(input[0], "ps", 2) == 0)
															return (0);
	else
		return (1);
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
		printf("command not found: No such file or directory\n");
		return (0);
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
		curr = curr->next;
	}
}

char	**pipe_loop(t_token **tail)
{
	char	*path;
	char	**command_seq;

	check_redirects(tail);
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

int	new_executor(t_token **tail, t_shell *data, char **envp)
{
	int			pipefd[4];
	int			file[1024];
	t_type		file_type[1024];
	t_token		*tmp;
	char		**comm_seq;

	data = data;
	tmp = *tail;
	pipefd[2] = dup(0);
	pipefd[3] = dup(1);
	while (*tail)
	{
		files_open(file, file_type, tail, pipefd);
		if (file_type[0] != PRINTABLE)
			redirect_infiles(file, file_type, tail);
		comm_seq = pipe_loop(tail);
		if (execute_comm(comm_seq, data) == 0)
			comm_forker(comm_seq , envp, pipefd, check_pipe(tail, file_type));
		close_doc(file, file_type);
		if ( *tail && (*tail)->typ_token == PIPELINE)
			*tail = (*tail)->next;
		/* if ((*tail)->typ_token == COMMAND) */
		/* 	execute_comm(*tail, input, data); */
	}
	dup2(pipefd[2], 0);
	dup2(pipefd[3], 1);
	*tail = tmp;
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
