#include "minishell.h"

// void	ft_executor(t_shell *data, t_token **token, char *args, char **env)
// {
// 	t_token	*curr;
// 	env = env;
// 	char **input;

// 	args = args;
// 	curr = *token;
// 	input = seq_extract(token);
// 	while (curr)
// 	{
// 		if(curr->typ_token == COMMAND)
// 		{
// 			printf("%s\n", curr->content);
// 			if (ft_strncmp(curr->content, "ls", 3) == 0)
// 				ft_ls();//ft_ls();
// 			else if(ft_strncmp(curr->content, "env", 3) == 0)
// 				ft_env(data);
// 			else if(ft_strncmp(curr->content, "export", 6) == 0)
// 				ft_export(data, input);
// 			else if(ft_strncmp(curr->content, "unset", 5) == 0)
// 				ft_unset(data, input);
// 			else if(ft_strncmp(curr->content, "pwd", 3) == 0)
// 				ft_pwd();
// 			else if(ft_strncmp(curr->content, "echo", 4) == 0)
// 				ft_echo(input);
// 			else
// 				printf("\nnull\n");
// 		}
// 		curr = curr->next;
// 	}
// }
