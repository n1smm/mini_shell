#include "minishell.h"

void	ft_executor(t_token **token, char **args, char **env)
{
	t_token	*curr;
	t_env_var	**tail;
	/* int i =0; */
	// t_env_var **head;
	/* t_shell	*var; */

	/* var->env = NULL; */
	//printf("FT_EXECUTOR\n");
	tail = NULL;
	// head = NULL;
	if(!token || !*token)
		return ;
	// init_env_vars(tail, head);
	args = args;
	curr = *token;
	while (curr)
	{
		//printf("%s\n", (*token)->content);
		//printf("%d\n", (*token)->typ_token);
		if(curr->typ_token == COMMAND)
		{
			printf("%s\n", curr->content);
			if (ft_strncmp(curr->content, "ls", 3) == 0)
				ft_ls();
			else if(ft_strncmp(curr->content, "env", 3) == 0)
				ft_env(*tail, env);
			else if(ft_strncmp(curr->content, "export", 6) == 0)
				;
				/* ft_export(var, env); */
			else if(ft_strncmp(curr->content, "pwd", 3) == 0)
				ft_pwd();
			else if(ft_strncmp(curr->content, "echo", 4) == 0)
			{
				ft_echo(args);
				// printf("ECHO\n");
				// while (args[i])
				// {
				// 	ft_putstr_fd(args[i], 1);
				// 	i++;
				// }
				//printf("%s\n", curr->next->next->content);
				//ft_echo(curr->next->next->content);
			}
			else
				printf("\nnull\n");
		}
		curr = curr->next;
	}
}
